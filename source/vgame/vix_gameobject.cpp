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

namespace Vixen {

	GameObject::GameObject()
	{
		m_id = 0;
		m_enabled = false;
		m_model = NULL;
		m_parent = NULL;
		m_transform = NULL;
	}

	GameObject::GameObject(Transform* transform)
	{
		m_id = 0;
		m_enabled = false;
		m_model = NULL;
		m_parent = NULL;
		m_transform = transform;
	}

	GameObject::GameObject(Transform* transform, IModel* model)
	{
		m_id = 0;
		m_enabled = false;
		m_parent = NULL;
		m_transform = transform;
		m_model = model;
	}

	GameObject::~GameObject()
	{
		SetEnabled(false, false);

		for (size_t i = 0; i < m_components.size(); i++)
		{
			IComponent* component = m_components[i];
			if (component)
			{
				component->VOnDestroy();
			}
		}

		for (int i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];
			if(_child)
				delete _child;
		}
        delete m_transform;
	}

	void GameObject::SetModel(IModel* model)
	{
		m_model = model;
		m_model->VSetWorld(m_transform->GetWorldMatrix());
	}

	void GameObject::AddComponent(IComponent* component)
	{
		m_components.push_back(component);
		component->VOnInit();
		if(m_enabled)
			component->VOnEnable();
	}

	void GameObject::Update(float dt)
	{
		for (size_t i = 0; i < m_components.size(); i++)
		{
			IComponent* component = m_components[i];
			if (component)
				component->VUpdate(dt);
		}

		for (int i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];
			if(_child->GetEnabled())
				_child->Update(dt);
		}
	}

	void GameObject::Render(float dt, ICamera3D * camera)
	{
		if (m_model) {
			m_model->VBatchRender(m_transform->GetWorldMatrix());
		}
		
		for (int i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];

			if (_child->GetEnabled())
				_child->Render(dt, camera);
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
		ObjectManager::DestroyGameObject(this);
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
				for (size_t i = 0; i < m_components.size(); i++)
				{
					IComponent* component = m_components[i];
					if (component)
						component->VOnEnable();
				}
			}
			//loop through components and disable them
			else
			{
				for (size_t i = 0; i < m_components.size(); i++)
				{
					IComponent* component = m_components[i];
					if (component)
						component->VOnDisable();
				}
			}
		}
		if(recursive)
		{
			for (int i = 0; i < m_children.size(); i++)
			{
				GameObject* _child = m_children[i];

				_child->SetEnabled(state, recursive);
			}
		}
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

		m_children.push_back(gameObject);
		gameObject->m_parent = this;
		m_transform->AddChildTransform(gameObject->GetTransform());
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
		if (index >= m_children.size())
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