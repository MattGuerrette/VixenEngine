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

#include <vix_prefabmanager.h>
#include "vix_tinyxml.h"
#include "vix_filemanager.h"
#include "vix_pathmanager.h"
#include <vix_scenemanager.h>
#include <vix_luascriptmanager.h>
#include <vix_components.h>
#include "vix_resourcemanager.h"

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
		while(it != _manager.m_prefabs.end())
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

		File* _prefabFile = FileManager::OpenFile(PathManager::PrefabPath() + file, FileMode::ReadBinary);
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
				_component = ParseLuaScriptComponent(child);
			}
			else if (name == "camera")
			{
				//PARSE CAMERA
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
			else if (name == "model")
			{
				_component = ParseModelComponent(child);
			}

			if (_component != NULL)
				prefab->AddComponent(_component);

			child = child->NextSiblingElement();
		}
	}

	Component* PrefabManager::ParseUITextComponent(const tinyxml2::XMLElement* element)
	{
        using namespace tinyxml2;

        const char* text = element->Attribute("text");
        const char* font = element->Attribute("font");


        Font*  _font = ResourceManager::OpenFont(UStringFromCharArray(font));
        _font->IncrementRefCount();

        UIText* _text = new UIText(UStringFromCharArray(text), _font);

        return _text;
	}

	Component* PrefabManager::ParseCameraComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		Camera3DComponent* _camera = new Camera3DComponent();
		const XMLElement* _viewportElement = element->FirstChildElement("viewport");
		if (_viewportElement)
		{
			float x = _viewportElement->FloatAttribute("x");
			float y = _viewportElement->FloatAttribute("y");
			float width = _viewportElement->FloatAttribute("width");
			float height = _viewportElement->FloatAttribute("height");
			float minDepth = _viewportElement->FloatAttribute("min");
			float maxDepth = _viewportElement->FloatAttribute("max");

			Viewport v;
			v.x = x;
			v.y = y;
			v.width = width;
			v.height = height;
			v.minDepth = minDepth;
			v.maxDepth = maxDepth;

			_camera->GetCamera()->VSetViewport(v);
		}

		return _camera;
	}

	Component* PrefabManager::ParseLightComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		std::string type(element->Attribute("type"));
		if (type == "point") {

			PointLightComponent* light = new PointLightComponent;

			const XMLElement* colorElement = element->FirstChildElement("color");
			if (colorElement)
			{
				float r = colorElement->FloatAttribute("r");
				float g = colorElement->FloatAttribute("g");
				float b = colorElement->FloatAttribute("b");
				float a = colorElement->FloatAttribute("a");
				light->SetColor({ r, g, b, a });
			}

			const XMLElement* attenElement = element->FirstChildElement("attenuation");
			if (attenElement)
			{
				float range = attenElement->FloatAttribute("range");
				float constant = attenElement->FloatAttribute("constant");
				float linear = attenElement->FloatAttribute("linear");
				float quadratic = attenElement->FloatAttribute("quadratic");

				light->SetRange(range);
				light->SetConstant(constant);
				light->SetLinear(linear);
				light->SetQuadratic(quadratic);
			}

			return light;
		}
		else if (type == "directional") {
			/*float dirX = element->FloatAttribute("dirX");
			float dirY = element->FloatAttribute("dirY");
			float dirZ = element->FloatAttribute("dirZ");
			light = new DirectionalLight;
			light->m_ambientColor = Vector3(red, green, blue);
			((DirectionalLight*)light)->m_direction = Vector3(dirX, dirY, dirZ);*/
		}
		else {
			/*light = new ILight;
			light->m_ambientColor = Vector3(red, green, blue);*/
		}

		return nullptr;
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

	Component* PrefabManager::ParseModelComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* file = element->Attribute("file");
		const char* materialFile = element->Attribute("material");

		Model* _model = (Model*)ResourceManager::AccessAsset(UStringFromCharArray(file));
		if (!_model) {
			_model = ResourceManager::OpenModel(UStringFromCharArray(file));
			if (!_model) {
				DebugPrintF(VTEXT("Failed to open model.\n"));
				return NULL;
			}
		}
		_model->IncrementRefCount();

		Material* _material = ResourceManager::OpenMaterial(UStringFromCharArray(materialFile));
		if (!_material) {
			DebugPrintF(VTEXT("Failed to open material.\n"));
			return NULL;
		}
		_material->IncrementRefCount();

		ModelComponent* _modelComponent = new ModelComponent;
		_modelComponent->SetModel(_model);
		_modelComponent->SetMaterial(_material);

		return _modelComponent;
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
		ParseTransform(_newPrefab, transform);


		//PARSE PREFAB MODEL
		const XMLElement* model = element->FirstChildElement("model");
		if(model)
			_newPrefab->SetModelFile(model->Attribute("file"));

		//PARSE PREFAB COMPONENTS
		const XMLElement* components = element->FirstChildElement("components");
		if (components)
			ParseComponents(_newPrefab, components);

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
