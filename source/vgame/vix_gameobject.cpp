/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_gameobject.h>
#include <vix_lua.h>
#include <vix_luaengine.h>
#include <vix_objectmanager.h>
#include <vix_scenemanager.h>

#include <vix_components.h>
#include <vix_component.h>

#include <vix_renderer_singleton.h>

namespace Vixen {

    GameObject* GameObject::s_ActiveObject = NULL;

    void GameObject::_TranslateZ(float val)
    {
        GameObject::s_ActiveObject->GetTransform()->TranslateZ(val);
    }

    GameObject* GameObject::_GetActiveObject()
    {
        return s_ActiveObject;
    }

    Transform* GameObject::_GetTransform()
    {
        return GameObject::s_ActiveObject->GetTransform();
    }

    float GameObject::_GetTransformZ()
    {
        return GameObject::s_ActiveObject->GetTransform()->Z();
    }

    void GameObject::_SetTransformPosition(Vector3 v)
    {
        GameObject::s_ActiveObject->GetTransform()->SetPosition(v);
    }

    Vector3 GameObject::_GetTransformPosition()
    {
        return GameObject::s_ActiveObject->GetTransform()->GetPosition();
    }

    GameObject::GameObject()
	{
		m_id = 0;
		m_enabled = false;
		m_parent = NULL;
		m_transform = NULL;
		m_markedForDestroy = false;
        m_markedForLateRender = false;
	}

	GameObject::GameObject(Transform* transform)
	{
		m_id = 0;
		m_enabled = false;
		m_parent = NULL;
		m_transform = transform;
		m_markedForDestroy = false;
        m_markedForLateRender = false;
	}

	GameObject::~GameObject()
	{
		SetEnabled(false, false);

		for (uint32_t i = 0; i < m_components.size(); i++)
		{
			Component* component = m_components[i];
			if (component)
			{
                component->VOnDisable();
				component->VOnDestroy();
                delete component;
			}
		}

		for (uint32_t i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];
			if (_child)
			{
				delete _child;
			}

		}
        delete m_transform;
	}



	void GameObject::AddComponent(Component* component)
	{
		m_components.push_back(component);
		component->VOnInit();
		if(m_enabled)
			component->VOnEnable();
	}

	void GameObject::Update()
	{
		for (uint32_t i = 0; i < m_components.size(); i++)
		{
			Component* component = m_components[i];
			if (component)
				component->VUpdate();
		}

		for (uint32_t i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];
			if (_child->IsMarkedForDestroy())
			{
				ObjectManager::DestroyGameObject(_child);
				m_children.erase(m_children.begin() + i);
				i--;
			}
			else if(_child->GetEnabled())
				_child->Update();
		}
	}

	void GameObject::Render(ICamera3D * camera)
	{
        for (uint32_t i = 0; i < m_components.size(); i++)
        {
            IRenderComponent2D* _renderComponent2D = dynamic_cast<IRenderComponent2D*>(m_components[i]);
			if (_renderComponent2D) {
				_renderComponent2D->VRender(Renderer::Camera2D(), camera->VGetViewport());
			}


			IRenderComponent* _renderComponent = dynamic_cast<IRenderComponent*>(m_components[i]);
			if (_renderComponent)
				_renderComponent->VRender(camera);

        }

		for (uint32_t i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];

			if (!_child->IsMarkedForDestroy() && _child->GetEnabled())
				_child->Render(camera);
		}
	}

	bool GameObject::GetEnabled()
	{
		return m_enabled;
	}

	GameObject* GameObject::GetParent()
	{
		return m_parent;
	}

	void GameObject::Delete()
	{
		m_markedForDestroy = true;
	}

	void GameObject::SetEnabled(bool state, bool recursive)
	{
		//only do code if this changes the state
		if (m_enabled != state)
		{
			m_enabled = state;

			//loop through components and enable them
			if (m_enabled)
			{
				for (uint32_t i = 0; i < m_components.size(); i++)
				{
					Component* component = m_components[i];
					if (component)
						component->VOnEnable();
				}
			}
			//loop through components and disable them
			else
			{
				for (uint32_t i = 0; i < m_components.size(); i++)
				{
					Component* component = m_components[i];
					if (component)
						component->VOnDisable();
				}
			}
		}
		if(recursive)
		{
			for (uint32_t i = 0; i < m_children.size(); i++)
			{
				GameObject* _child = m_children[i];

				_child->SetEnabled(state, recursive);
			}
		}
	}

	bool GameObject::IsMarkedForDestroy()
	{
		return m_markedForDestroy;
	}

    bool GameObject::IsMarkedForLateRender()
    {
        return m_markedForLateRender;
    }

    void GameObject::MarkForLateRender()
    {
        m_markedForLateRender = true;
    }

	void GameObject::AddChild(GameObject* gameObject)
	{
		//go up in parents until there's nothing left, or we hit a match
		GameObject* current = m_parent;
		while (current) {
			//if the new child owns this gameobject as a parent, we can't parent
			if (current == gameObject)
				return;
			current = current->m_parent;
		}
		//if the given object isn't a parent we can child it to this object

		//but first we have to remove it from the previous parent
		//first case: there is no parent, attempt to remove from scene
		if (!gameObject->m_parent)
		{
			SceneManager::ActiveScene()->RemoveSceneObject(gameObject);
		}
		//second case there is a parent remove it from that object
		else
		{
			gameObject->m_parent->RemoveChild(gameObject);
			m_transform->RemoveChildTransform(gameObject->GetTransform());
		}

		//now we can add it to this object
		m_children.push_back(gameObject);


		gameObject->m_parent = this;
		m_transform->AddChildTransform(gameObject->GetTransform());
	}

	void GameObject::RemoveChild(GameObject * gameObject)
	{
		for (uint32_t i = 0; i < m_children.size(); i++)
		{
			if (m_children.at(i) == gameObject)
			{
				m_children.erase(m_children.begin()+i);
				return;
			}
		}
	}

	Transform* GameObject::GetTransform()
	{
		return m_transform;
	}

	Transform& GameObject::GetTransformRef()
	{
		return *m_transform;
	}

	GameObject* GameObject::GetChild(int index)
	{
		if ((uint32_t)index >= m_children.size())
			return NULL;

		return m_children[index];
	}

	void GameObject::SetName(UString name)
	{
		m_name = name;
	}

	uint32_t GameObject::GetID()
	{
		return m_id;
	}

	void GameObject::SetID(uint32_t id)
	{
		m_id = id;
	}

	std::string GameObject::GetName()
	{
		return UStringToStd(m_name);
	}

}
