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

#include <vix_scene.h>
#include <vix_modelmanager.h>
#include <vix_stlutil.h>
#include <vix_scenemanager.h>
#include <vix_objectmanager.h>
#include <vix_time.h>
#include <vix_resourcemanager.h>

#include <vix_components.h>

namespace Vixen {



	/////////////////////////////////////////////////
	// Scene implementation
	/////////////////////////////////////////////////

	Scene::Scene()
	{
		m_paused = false;
		m_hidden = false;

		m_mainCamera = NULL;
	}

	Scene::~Scene()
	{
		if (m_topLevelObjects.size() > 0)
			STLVEC_DELETE(m_topLevelObjects);
	}

	void Scene::AddSceneObject(GameObject* object)
	{
		m_topLevelObjects.push_back(object);
	}

	void Scene::RemoveSceneObject(GameObject* object)
	{
		for (int i = 0; i < m_topLevelObjects.size(); i++)
		{
			if (m_topLevelObjects.at(i) == object)
			{
				m_topLevelObjects.erase(m_topLevelObjects.begin() + i);
				return;
			}
		}
	}


	void Scene::Update()
	{
		//update all scene objects
		for (int i = 0; i < m_topLevelObjects.size(); i++)
		{
			GameObject* obj = m_topLevelObjects.at(i);
			if(obj->IsMarkedForDestroy())
			{
				//destroy the object and skip over the index
				ObjectManager::DestroyGameObject(obj);
				m_topLevelObjects.erase(m_topLevelObjects.begin() + i);
				i--;
			}
			else if (obj->GetEnabled())
				obj->Update();
		}
	}

	void Scene::Render()
	{
		//render all scene object
		for (int i = 0; i < m_topLevelObjects.size(); i++)
		{
			GameObject* obj = m_topLevelObjects.at(i);
			if (!obj->IsMarkedForDestroy() && !obj->IsMarkedForLateRender() && obj->GetEnabled())
				obj->Render(m_mainCamera);
		}

		for (auto& model : ModelManager::ActiveModels())
			model->VRender(Time::DeltaTime(), Time::TotalTime(), m_mainCamera);

        //render all late render (UI) scene objects
        //NOTE: this is expensive, as we are iterating over the list of objects again...
        //      what should happen is the list should be sorted once, leaving all late render objects
        //      last to be drawn.
        for (int i = 0; i < m_topLevelObjects.size(); i++)
        {
            GameObject* obj = m_topLevelObjects.at(i);
            if (obj->IsMarkedForLateRender() && obj->GetEnabled())
                obj->Render(m_mainCamera);
        }

	}

	GameObject* Scene::QueryObject(std::string name)
	{
		for (int i = 0; i < m_topLevelObjects.size(); i++)
		{
			GameObject* _object = m_topLevelObjects[i];
			if (_object->GetName() == name)
				return _object;
		}

		return NULL;
	}

	/*SETTER FUNCTIONS*/

	void Scene::SetID(std::string id)
	{
		m_id = id;
	}

	void Scene::SetFileName(std::string name)
	{
		m_fileName = name;
	}

	void Scene::SetMainCamera(ICamera3D * camera)
	{
		m_mainCamera = camera;
	}

	void Scene::SetPaused(bool paused)
	{
		m_paused = paused;
	}

	void Scene::SetHidden(bool hidden)
	{
		m_hidden = hidden;
	}



	/*GETTER FUNCTIONS*/
	const std::string& Scene::GetID()
	{
		return m_id;
	}

	const std::string& Scene::GetFileName()
	{
		return m_fileName;
	}

	bool Scene::IsPaused()
	{
		return m_paused;
	}

	bool Scene::IsHidden()
	{
		return m_hidden;
	}




	///////////////////////////////////////////////////////////////////////
	// STATIC FUNCTIONS
	///////////////////////////////////////////////////////////////////////

	Scene* Scene::Deserialize(File* file)
	{

		using namespace tinyxml2;

		//File is actually an XML file
		//we should now open for reading
		XMLDOC document;
		XMLError err = document.LoadFile(file->Handle());
		UString errString;
		if (XMLErrCheck(err, errString))
		{
			DebugPrintF(VTEXT("Scene File failed to load\n"));
			return NULL;
		}

		Scene* _scene = new Scene;
		SceneManager::AddScene(_scene);

		const XMLElement* sceneElement = document.FirstChildElement("scene");
		const XMLElement* objectListElement = sceneElement->FirstChildElement("object-list");
		const XMLElement* gameObjectElement = objectListElement->FirstChildElement("gameobject");
		const char* sceneID = sceneElement->Attribute("id");
		_scene->SetID(sceneID);
		while (gameObjectElement != NULL)
		{
			GameObject* _gameObject = ParseGameObject(_scene, gameObjectElement);

			_scene->AddSceneObject(_gameObject);

			gameObjectElement = gameObjectElement->NextSiblingElement("gameobject");
		}

		/////////////////////////////////////////////////////
		// temporary until objects have their enabled status serialized
		//////////////////////////////////////////
		/*for (auto& obj : _scene->m_sceneObjects)
			obj.second->SetEnabled(true, true);
		*/
		return _scene;
	}

	GameObject* Scene::ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* objectName = element->Attribute("name");
		const bool enabled = element->BoolAttribute("enabled");

		Transform * transform = ParseTransform(element->FirstChildElement("transform"));

		const XMLElement* model = element->FirstChildElement("model");
		std::string modelFile = "";
		if (model) {
			modelFile = model->Attribute("file");
		}

		GameObject* _object = new GameObject(transform,
			ModelManager::AccessModel(UStringFromCharArray(modelFile.c_str())));
		_object->SetName(UStringFromCharArray(objectName));
		_object->SetEnabled(enabled, false);
		ObjectManager::MapSceneObject(_object);

		std::vector<Component*> components = ParseComponents(scene, element->FirstChildElement("components"));
		for (auto& component : components)
		{
			component->VBindParent(_object);
			_object->AddComponent(component);
		}

		//PARSE CHILD OBJECTS OBJECTS
		const XMLElement* children = element->FirstChildElement("children");
		if (children)
		{
			const XMLElement* objectElement = children->FirstChildElement("gameobject");
			while (objectElement != NULL)
			{
				GameObject* _child = ParseGameObject(scene, objectElement);
				_object->AddChild(_child);
				objectElement = objectElement->NextSiblingElement("gameobject");
			}

		}

		return _object;
	}

	Transform* Scene::ParseTransform(const tinyxml2::XMLElement * element)
	{
		if (!element)
			return nullptr;
		float posX = element->FloatAttribute("x");
		float posY = element->FloatAttribute("y");
		float posZ = element->FloatAttribute("z");
		float rotX = element->FloatAttribute("rotX");
		float rotY = element->FloatAttribute("rotY");
		float rotZ = element->FloatAttribute("rotZ");
		float scaleX = element->FloatAttribute("scaleX");
		float scaleY = element->FloatAttribute("scaleY");
		float scaleZ = element->FloatAttribute("scaleZ");
		return new Transform(posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ);
	}

	std::vector<Component*> Scene::ParseComponents(Scene* scene, const tinyxml2::XMLElement * element)
	{
		using namespace tinyxml2;

		std::vector<Component*> components;

		const XMLElement* child = element->FirstChildElement();
		while (child) {
			std::string name(child->Name());

			Component* component = NULL;
			if (name == "script")
			{
				//PARSE SCRIPT
				//component = ParseLuaScriptComponent(child);
			}
			else if (name == "camera")
			{
				//PARSE CAMERA
				component = ParseCameraComponent(scene, child);
			}
			else if (name == "light")
			{
				//PARSE LIGHT
				component = ParseLightComponent(child);
			}
            else if (name == "ui-text")
            {
                //PARSE UI-TEXT
                component = ParseUITextComponent(child);
            }

			if (component)
				components.push_back(component);

			child = child->NextSiblingElement();
		}

		return components;
	}

	Component* Scene::ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement * element)
	{
		bool isMainCamera = element->BoolAttribute("mainCamera");
		Camera3DComponent* _camera = new Camera3DComponent;
		if (isMainCamera)
			scene->m_mainCamera = _camera->GetCamera();
		return _camera;
	}

    Component* Scene::ParseLightComponent(const tinyxml2::XMLElement * element)
	{
		using namespace tinyxml2;

		ILight* light;
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

    Component* Scene::ParseUITextComponent(const tinyxml2::XMLElement* element)
    {
        using namespace tinyxml2;

        const char* text = element->Attribute("text");
        const char* font = element->Attribute("font");


        IFont*  _font = ResourceManager::OpenFont(UStringFromCharArray(font));
        UIText* _text = new UIText(UStringFromCharArray(text), _font);

        return _text;
    }
}
