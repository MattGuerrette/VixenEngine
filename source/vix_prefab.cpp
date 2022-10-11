/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#include <vix_prefab.h>
#include "vix_stlutil.h"
#include <vix_scenemanager.h>
#include <vix_luascriptmanager.h>
#include <vix_luascript.h>
#include <vix_objectmanager.h>
#include "vix_resourcemanager.h"
#include <vix_components.h>
#include <vix_window_singleton.h>

namespace Vixen {

	Prefab::Prefab()
	{
		m_refCount = 0;
	}

	Prefab::~Prefab()
	{
		for (auto& c : m_components)
			c->VOnDestroy();

		STLVEC_DELETE(m_components);
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
		GameObject* _object = new GameObject(_objectTransform);
		_object->SetName(UStringFromCharArray(prefab->GetName().c_str()));
		_object->SetEnabled(prefab->GetEnabled(), false);
		ObjectManager::MapSceneObject(_object);


		uint32_t numComponents = prefab->m_components.size();
		for (uint32_t i = 0; i < numComponents; i++)
		{
			Component* component = prefab->m_components[i];

			if (component)
			{
				Component::Type type = component->VGetType();
				switch (type)
				{
					case Component::Type::UNUSED:
						break;

					case Component::Type::LUA_SCRIPT:
					{

						//Should be able to be created from copy construct not reloading.
						LuaScript* _script = LuaScriptManager::LoadScript(((LuaScript*)component)->GetPath());
						_script->VBindParent(_object);
						_object->AddComponent(_script);

					} break;

					case Component::Type::MODEL:
					{
						ModelComponent* _modelComponent = (ModelComponent*)component;

						ModelComponent* _newComponent = new ModelComponent;
						_modelComponent->GetModel()->IncrementRefCount();
						_modelComponent->GetMaterial()->IncrementRefCount();
						_newComponent->SetModel(_modelComponent->GetModel());
						_newComponent->SetMaterial(_modelComponent->GetMaterial());

						_newComponent->VBindParent(_object);
						_object->AddComponent(_newComponent);
					} break;

					case Component::Type::CAMERA:
					{
						Camera3DComponent* _cameraComponent = (Camera3DComponent*)component;

						Camera3DComponent* _newCamera = new Camera3DComponent();

						//copy camera viewports
						Viewport v = _cameraComponent->GetCamera()->VGetViewport();
						v.sWidth = Window::Width();
						v.sHeight = Window::Height();
						_newCamera->GetCamera()->VSetViewport(v);


						_newCamera->VBindParent(_object);
						_object->AddComponent(_newCamera);

					} break;

					case Component::Type::POINT_LIGHT:
					{

						PointLightComponent* _component = (PointLightComponent*)component;

						PointLightComponent* _newComponent = new PointLightComponent;
						_newComponent->SetLight(_component->GetLight());

						_newComponent->VBindParent(_object);
						_object->AddComponent(_newComponent);

					} break;

					case Component::Type::UI_TEXT:
					{
                        UIText* _textComponent = (UIText*)component;
                        _textComponent->GetFont()->IncrementRefCount();

                        UIText* _newText = new UIText(_textComponent->GetTextW(), _textComponent->GetFont());

                        _newText->VBindParent(_object);
                        _object->AddComponent(_newText);

					} break;

					case Component::Type::UI_BUTTON:
					case Component::Type::UI_TEXTURE:
					case Component::Type::SPRITE:
					case Component::Type::PHYSICS_RIGIDBODY:
						break;

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
		if ((uint32_t)index > m_children.size())
			return NULL;
		else
			return m_children[index];
	}

	std::string Prefab::GetScriptFile(int index)
	{
		if ((uint32_t)index > m_scriptFiles.size())
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
