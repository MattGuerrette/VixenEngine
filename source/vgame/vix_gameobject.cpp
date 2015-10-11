/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vix_gameobject.h>
#include <vix_lua.h>
#include <vix_luaengine.h>
#include <vix_objectmanager.h>

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

	void GameObject::Update()
	{
		for (size_t i = 0; i < m_components.size(); i++)
		{
			IComponent* component = m_components[i];
			if (component)
				component->VUpdate();
		}

		/*for (int i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];
			if(_child->GetEnabled())
				_child->Update(dt);
		}*/
	}

	void GameObject::Render(ICamera3D * camera)
	{
		if (m_model) {
			m_model->VBatchRender(m_transform->GetWorldMatrix());
		}

		for (int i = 0; i < m_children.size(); i++)
		{
			GameObject* _child = m_children[i];

			if (_child->GetEnabled())
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
