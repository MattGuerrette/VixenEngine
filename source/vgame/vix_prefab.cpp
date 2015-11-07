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

#include <vix_prefab.h>
#include <vix_stlutil.h>
#include <vix_scenemanager.h>
#include <vix_modelmanager.h>
#include <vix_component.h>
#include <vix_objectmanager.h>

namespace Vixen {

	Prefab::Prefab()
	{
		m_refCount = 0;
	}

	Prefab::~Prefab()
	{
		STLVEC_DELETE(m_children);
	}


	std::string Prefab::GetName()
	{
		return m_name;
	}

	bool Prefab::GetEnabled()
	{
		return m_enabled;
	}

	std::string Prefab::GetModelFile()
	{
		return m_modelFile;
	}

	Transform Prefab::GetTransform()
	{
		return m_transform;
	}

	void Prefab::SetName(std::string name)
	{
		m_name = name;
	}

	void Prefab::SetEnabled(bool enabled)
	{
		m_enabled = enabled;
	}

	void Prefab::SetTransform(Transform t)
	{
		m_transform = t;
	}

	void Prefab::SetModelFile(std::string file)
	{
		m_modelFile = file;
	}

	void Prefab::AddChild(Prefab* child)
	{
		m_children.push_back(child);
	}

	void Prefab::AddScriptFile(std::string file)
	{
		m_scriptFiles.push_back(file);
	}

	GameObject* Prefab::BuildFromPrefab(Prefab* prefab)
	{
		//need to create game object with prefab data
		Vector3 _objectPos = prefab->GetTransform().GetPosition();
		Vector3 _objectRot = prefab->GetTransform().GetRotation();
		Vector3 _objectScale = prefab->GetTransform().GetScale();
		Transform* _objectTransform = new Transform(_objectPos, _objectRot, _objectScale);
		GameObject* _object = new GameObject(_objectTransform,
			ModelManager::AccessModel(UStringFromCharArray(prefab->GetModelFile().c_str())));
		_object->SetName(UStringFromCharArray(prefab->GetName().c_str()));
		_object->SetEnabled(prefab->GetEnabled(), false);
		ObjectManager::MapSceneObject(_object);



		uint32_t numComponents = prefab->m_components.size();
		for (uint32_t i = 0; i < numComponents; i++)
		{
			Component* component = prefab->m_components[i];

			if (component)
			{
				switch (component->VGetType())
				{
					case Component::Type::LUA_SCRIPT:
					{

						//Should be able to be created from copy construct not reloading.
						/*LuaScript* _script = LuaScriptManager::LoadScript(((LuaScript*)component)->GetPath());
						_script->VBindParent(_object);
						_object->AddComponent(_script);*/

					} break;

					case Component::Type::UI_TEXT:
					{



					} break;
				}
			}
		}

		//build children
		size_t numChildren = prefab->ChildCount();
		for (size_t i = 0; i < numChildren; i++)
		{
			Prefab* _child = prefab->GetChild(i);

			_object->AddChild(BuildFromPrefab(_child));
		}

		return _object;
	}

	GameObject* Prefab::CreateObject()
	{
		GameObject* _object = BuildFromPrefab(this);

		SceneManager::ActiveScene()->AddSceneObject(_object);

		return _object;
	}

	void Prefab::AddComponent(Component* component)
	{
		m_components.push_back(component);
	}

	void Prefab::IncRefCount()
	{
		m_refCount++;
	}

	void Prefab::DecRefCount()
	{
		if (m_refCount > 0)
			m_refCount--;
	}

	uint32_t Prefab::RefCount()
	{
		return m_refCount;
	}

	Prefab* Prefab::GetChild(int index)
	{
		if (index > m_children.size())
			return NULL;
		else
			return m_children[index];
	}

	std::string Prefab::GetScriptFile(int index)
	{
		if (index > m_scriptFiles.size())
			return NULL;
		else
			return m_scriptFiles[index];
	}

	size_t Prefab::ScriptCount()
	{
		return m_scriptFiles.size();
	}

	size_t Prefab::ChildCount()
	{
		return m_children.size();
	}
}
