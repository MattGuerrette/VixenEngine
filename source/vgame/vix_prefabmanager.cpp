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

	Prefab* PrefabManager::ParsePrefab(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		Prefab* _newPrefab = new Prefab;

		std::string name = element->Attribute("defaultName");
		_newPrefab->SetName(name);
		_newPrefab->SetEnabled(element->BoolAttribute("enabled"));

		const XMLElement* transform = element->FirstChildElement("transform");
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

		const XMLElement* model = element->FirstChildElement("model");
		_newPrefab->SetModelFile(model->Attribute("file"));

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
