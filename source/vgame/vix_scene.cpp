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

#include <vix_scene.h>
#include <vix_stlutil.h>
#include <vix_luascriptmanager.h>
#include <vix_scenemanager.h>
#include <vix_objectmanager.h>
#include <vix_time.h>
#include <vix_luaengine.h>
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

		for (uint32_t i = 0; i < ResourceManager::NumLoadedModels(); i++)
		{
			IModel* model = ResourceManager::ModelAsset(i);
			if (model)
				model->VRender(Time::DeltaTime(), Time::TotalTime(), m_mainCamera);
		}

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

		LuaEngine::ExecuteExpression(VTEXT("collectgarbage()"));
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

		GameObject* _object = new GameObject(transform);
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
            else if (name == "ui-text")
            {
                //PARSE UI-TEXT
                component = ParseUITextComponent(child);
            }
			else if (name == "model")
			{
				//PARSE MODEL COMPONENT
				component = ParseModelComponent(child);
			}

			components.push_back(component);
			child = child->NextSiblingElement();
		}

		return components;
	}

	IComponent* Scene::ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement * element)
	{
		bool isMainCamera = element->BoolAttribute("mainCamera");
		Camera3DComponent* _camera = new Camera3DComponent;
		if (isMainCamera)
			scene->m_mainCamera = _camera->GetCamera();
		return _camera;
	}

    IComponent* Scene::ParseLightComponent(const tinyxml2::XMLElement * element)
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

    IComponent* Scene::ParseLuaScriptComponent(const tinyxml2::XMLElement * element)
	{
		using namespace tinyxml2;

		const char* scriptFile = element->Attribute("file");
		UString scriptPath = UStringFromCharArray(scriptFile);

		LuaScript* script = LuaScriptManager::LoadScript(scriptPath);
		return script;
	}

    IComponent* Scene::ParseUITextComponent(const tinyxml2::XMLElement* element)
    {
        using namespace tinyxml2;

        const char* text = element->Attribute("text");
        const char* font = element->Attribute("font");


        IFont*  _font = ResourceManager::OpenFont(UStringFromCharArray(font));
        UIText* _text = new UIText(UStringFromCharArray(text), _font);
        
        return _text;
    }

	IComponent* Scene::ParseModelComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* file = element->Attribute("file");
		const char* materialFile = element->Attribute("material");

		IModel* _model = ResourceManager::OpenModel(UStringFromCharArray(file));
		if (!_model) {
			DebugPrintF(VTEXT("Failed to open model.\n"));
			return NULL;
		}
			
		IMaterial* _material = ResourceManager::OpenMaterial(UStringFromCharArray(materialFile));
		if (!_material) {
			DebugPrintF(VTEXT("Failed to open material.\n"));
			return NULL;
		}

		ModelComponent* _modelComponent = new ModelComponent;
		_modelComponent->SetModel(_model);
		_modelComponent->SetMaterial(_material);
			
		return _modelComponent;
	}
}