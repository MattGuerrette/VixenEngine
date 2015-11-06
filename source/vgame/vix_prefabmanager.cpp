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

#include <vix_prefabmanager.h>
#include <vix_tinyxml.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_scenemanager.h>
#include <vix_luascriptmanager.h>
#include <vix_components.h>

namespace Vixen {

	bool PrefabManager::Initialize()
	{
		return true;

	}

	void PrefabManager::DeInitialize()
	{

	}

	Prefab* PrefabManager::GetPrefab(UString file)
	{
		PrefabManager& _manager = PrefabManager::instance();

		PrefabMap::iterator it = _manager.m_prefabs.find(file);
		if (it != _manager.m_prefabs.end())
			return it->second;
		else
			return NULL;
	}

	Prefab* PrefabManager::Load(std::string file)
	{
		UString _filePath = UStringFromCharArray(file.c_str());
		Prefab* _prefab = PrefabManager::GetPrefab(_filePath);

		if (!_prefab)
			_prefab = PrefabManager::LoadFile(_filePath);

		return _prefab;
	}

	void PrefabManager::Cleanup()
	{
		PrefabManager& _manager = PrefabManager::instance();

		PrefabMap::iterator it = _manager.m_prefabs.begin();
		for (it; it != _manager.m_prefabs.end();)
		{
			Prefab* _p = it->second;
			if (_p && _p->RefCount() == 0)
			{
				_manager.m_prefabs.erase(it++);
				delete _p;
			}
			else
				++it;
		}
	}

	Prefab* PrefabManager::LoadFile(UString file)
	{
		PrefabManager& _manager = PrefabManager::instance();


		using namespace tinyxml2;

		File* _prefabFile = FileManager::OpenFile(PathManager::PrefabPath() + file);
		if (_prefabFile)
		{
			//File is actually an XML file
			//we should now open for reading
			XMLDOC document;
			XMLError err = document.LoadFile(_prefabFile->Handle());
			UString errString;
			if (XMLErrCheck(err, errString))
			{
				DebugPrintF(VTEXT("Prefab File failed to load\n"));
                FileManager::CloseFile(_prefabFile);
				return NULL;
			}

			const XMLElement* prefab = document.FirstChildElement("prefab");
			const XMLElement* object = prefab->FirstChildElement("gameobject");
			if (prefab)
			{
				if (object)
				{
					Prefab* _prefab = ParsePrefab(object);

					_manager.m_prefabs[file] = _prefab;
                    FileManager::CloseFile(_prefabFile);
					return _prefab;
				}
			}
		}
		FileManager::CloseFile(_prefabFile);
		return NULL;
	}

	void PrefabManager::ParseTransform(Prefab* prefab, const tinyxml2::XMLElement* element)
	{
		if (!element || !prefab)
			return;

		float posX = element->FloatAttribute("x");
		float posY = element->FloatAttribute("y");
		float posZ = element->FloatAttribute("z");
		float rotX = element->FloatAttribute("rotX");
		float rotY = element->FloatAttribute("rotY");
		float rotZ = element->FloatAttribute("rotZ");
		float scaleX = element->FloatAttribute("scaleX");
		float scaleY = element->FloatAttribute("scaleY");
		float scaleZ = element->FloatAttribute("scaleZ");
		
		prefab->SetTransform(Transform(posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ));
	}

	void PrefabManager::ParseComponents(Prefab* prefab, const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const XMLElement* child = element->FirstChildElement();
		while (child) {

			std::string name(child->Name());
			Component* _component = NULL;
			if (name == "script")
			{
				//PARSE SCRIPT
				//prefab->AddScriptFile(ParseLuaScriptComponent(child));

				_component = ParseLuaScriptComponent(child);
			}
			else if (name == "camera")
			{
				//PARSE CAMERA
				//component = ParseCameraComponent(child);

				_component = ParseCameraComponent(child);
			}
			else if (name == "light")
			{
				//PARSE LIGHT
				

				_component = ParseLightComponent(child);
			}
			else if (name == "ui-text")
			{
				//PARSE UI TEXT

				_component = ParseUITextComponent(child);
			}

			if (_component != NULL)
				prefab->AddComponent(_component);

			child = child->NextSiblingElement();
		}
	}

	Component* PrefabManager::ParseUITextComponent(const tinyxml2::XMLElement* element)
	{
		return NULL;
	}

	Component* PrefabManager::ParseCameraComponent(const tinyxml2::XMLElement* element)
	{
		bool isMainCamera = element->BoolAttribute("mainCamera");
		Camera3DComponent* _camera = new Camera3DComponent;
		if (isMainCamera)
			SceneManager::ActiveScene()->SetMainCamera(_camera->GetCamera());
		return _camera;
	}

	Component* PrefabManager::ParseLightComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		ILight* light = NULL;
		float red = element->FloatAttribute("r");
		float green = element->FloatAttribute("g");
		float blue = element->FloatAttribute("b");

		std::string kind(element->Attribute("kind"));
		if (kind == "point") {
			float x = element->FloatAttribute("x");
			float y = element->FloatAttribute("y");
			float z = element->FloatAttribute("z");
			float radius = element->FloatAttribute("radius");

			light = new PointLight;
			light->m_ambientColor = Vector3(red, green, blue);
			((PointLight*)light)->m_position = Vector3(x, y, z);
			((PointLight*)light)->m_radius = radius;
		}
		else if (kind == "directional") {
			float dirX = element->FloatAttribute("dirX");
			float dirY = element->FloatAttribute("dirY");
			float dirZ = element->FloatAttribute("dirZ");
			light = new DirectionalLight;
			light->m_ambientColor = Vector3(red, green, blue);
			((DirectionalLight*)light)->m_direction = Vector3(dirX, dirY, dirZ);
		}
		else {
			light = new ILight;
			light->m_ambientColor = Vector3(red, green, blue);
		}
		LightComponent* component = new LightComponent(light);
		return component;
	}

	Component* PrefabManager::ParseLuaScriptComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* scriptFile = element->Attribute("file");
		UString scriptPath = UStringFromCharArray(scriptFile);

		LuaScript* script = LuaScriptManager::LoadScript(scriptPath);
		script->SetPath(scriptPath);

		return script;
	}

	Prefab* PrefabManager::ParsePrefab(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		Prefab* _newPrefab = new Prefab;

		std::string name = element->Attribute("name");
		_newPrefab->SetName(name);
		_newPrefab->SetEnabled(element->BoolAttribute("enabled"));

		//PARSE PREFAB TRANSFORM
		const XMLElement* transform = element->FirstChildElement("transform");
<<<<<<< HEAD
		float posX = transform->FloatAttribute("x");
		float posY = transform->FloatAttribute("y");
		float posZ = transform->FloatAttribute("z");
		float rotX = transform->FloatAttribute("rotX");
		float rotY = transform->FloatAttribute("rotY");
		float rotZ = transform->FloatAttribute("rotZ");
		float scaleX = transform->FloatAttribute("scaleX");
		float scaleY = transform->FloatAttribute("scaleY");
		float scaleZ = transform->FloatAttribute("scaleZ");
		_newPrefab->SetTransform(Transform(posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ));

=======
		ParseTransform(_newPrefab, transform);
		

		//PARSE PREFAB MODEL
>>>>>>> 5d61730afc80281f2da012a8e50084e490f8a879
		const XMLElement* model = element->FirstChildElement("model");
		if(model)
			_newPrefab->SetModelFile(model->Attribute("file"));

<<<<<<< HEAD
		const XMLElement* scripts = element->FirstChildElement("scripts");
		if (scripts)
		{
			const XMLElement* scriptNode = scripts->FirstChildElement("script");
			while (scriptNode != NULL)
			{
				const char* scriptFile = scriptNode->Attribute("file");

				_newPrefab->AddScriptFile(scriptFile);

				scriptNode = scriptNode->NextSiblingElement("script");
			}
		}
=======
		//PARSE PREFAB COMPONENTS
		const XMLElement* components = element->FirstChildElement("components");
		if (components)
			ParseComponents(_newPrefab, components);
>>>>>>> 5d61730afc80281f2da012a8e50084e490f8a879

		//PARSE PREFAB CHILDREN
		const XMLElement* children = element->FirstChildElement("children");
		if (children)
		{
			const XMLElement* childElement = children->FirstChildElement("gameobject");
			while (childElement != NULL)
			{
				Prefab* _child = ParsePrefab(childElement);

				_newPrefab->AddChild(_child);

				childElement = childElement->NextSiblingElement("gameobject");
			}
		}

		return _newPrefab;
	}
}
