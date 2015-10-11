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
#include <vix_luascriptmanager.h>
#include <vix_scenemanager.h>
#include <vix_objectmanager.h>
#include <vix_time.h>

namespace Vixen {



	/////////////////////////////////////////////////
	// Scene implementation
	/////////////////////////////////////////////////

	Scene::Scene()
	{
		m_paused = false;
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

	void Scene::QueObjectSpawn(GameObject* object)
	{
		m_objectsToAdd.push_back(object);
	}

	void Scene::QueObjectDestroy(GameObject* object)
	{
		m_objectsToRemove.push_back(object);
	}

	void Scene::Update()
	{
		if (m_paused)
			return;

		//update all scene objects
		for (auto& object : m_topLevelObjects)
			if (object->GetEnabled())
				object->Update();

		//spawn all queued objects
		for (auto& object : m_objectsToAdd)
		{
			this->AddSceneObject(object);
		}
		m_objectsToAdd.clear();

		DestroyObjects();
	}

	void Scene::Render()
	{
		//render all scene object
		for (auto& object : m_topLevelObjects)
			if (object->GetEnabled())
				object->Render(m_mainCamera);

		for (auto& model : ModelManager::ActiveModels())
			model->VRender(Time::DeltaTime(), Time::TotalTime(), m_mainCamera);
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

	void Scene::SetID(UString id)
	{
		m_id = id;
	}

	void Scene::DestroyObjects()
	{
		int numDestroy = m_objectsToRemove.size();

		int numTopLevelObjects = m_topLevelObjects.size();
		for (int i = 0; i < numDestroy; i++)
		{
			GameObject* _object = m_objectsToRemove[i];
			for (int j = 0; j < numTopLevelObjects; j++)
			{
				GameObject* _topLevel = m_topLevelObjects[j];
				if (_topLevel->GetID() == _object->GetID())
				{
					m_topLevelObjects.erase(m_topLevelObjects.begin() + j);
					ObjectManager::DestroySceneObject(_object->GetID());
					j--;
					numTopLevelObjects--;
				}
			}
		}

		m_objectsToRemove.clear();
	}

	void Scene::SetPaused(bool paused)
	{
		m_paused = paused;
	}


	/*GETTER FUNCTIONS*/
	const UString& Scene::GetID()
	{
		return m_id;
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
		_scene->SetID(UStringFromCharArray(sceneID));
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

//spawn all queued objects
		for (auto& object : _scene->m_objectsToAdd)
		{
			_scene->AddSceneObject(object);
		}
		_scene->m_objectsToAdd.clear();

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

		std::vector<IComponent*> components = ParseComponents(scene, element->FirstChildElement("components"));
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

	std::vector<IComponent*> Scene::ParseComponents(Scene* scene, const tinyxml2::XMLElement * element)
	{
		using namespace tinyxml2;

		std::vector<IComponent*> components;

		const XMLElement* child = element->FirstChildElement();
		while (child) {
			std::string name(child->Name());
			IComponent* component;
			if (name == "script")
			{
				//PARSE SCRIPT
				component = ParseLuaScriptComponent(child);
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

			components.push_back(component);
			child = child->NextSiblingElement();
		}

		return components;
	}

	CameraComponent* Scene::ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement * element)
	{
		bool isMainCamera = element->BoolAttribute("mainCamera");
		CameraComponent* _camera = new CameraComponent;
		if (isMainCamera)
			scene->m_mainCamera = _camera->GetCamera();
		return _camera;
	}

	LightComponent* Scene::ParseLightComponent(const tinyxml2::XMLElement * element)
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

	LuaScript* Scene::ParseLuaScriptComponent(const tinyxml2::XMLElement * element)
	{
		using namespace tinyxml2;

		const char* scriptFile = element->Attribute("file");
		UString scriptPath = UStringFromCharArray(scriptFile);

		LuaScript* script = LuaScriptManager::LoadScript(scriptPath);
		return script;
	}
}
