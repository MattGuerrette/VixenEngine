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

#include <vix_scene.h>
#include "vix_stlutil.h"
#include <vix_luascriptmanager.h>
#include <vix_scenemanager.h>
#include <vix_objectmanager.h>
#include <vix_time.h>
#include <vix_luaengine.h>
#include "vix_resourcemanager.h"
#include <vix_lightmanager.h>
#include <vix_components.h>
#include <vix_window_singleton.h>
#include "vix_renderer_singleton.h"

namespace Vixen
{



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
		for (uint32_t i = 0; i < m_topLevelObjects.size(); i++)
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
		for (uint32_t i = 0; i < m_topLevelObjects.size(); i++)
		{
			GameObject* obj = m_topLevelObjects.at(i);
			if (obj->IsMarkedForDestroy())
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

		//For each camera in the scene, we need to render all geometry and 
		//ui elements, twice. One for each camera viewport

		for (int i = 0; i < m_cameras.size(); i++)
		{

			ICamera3D* camera = m_cameras[i];

			//render all scene object
			for (int i = 0; i < m_topLevelObjects.size(); i++)
			{
				GameObject* obj = m_topLevelObjects.at(i);
				if (!obj->IsMarkedForDestroy() && !obj->IsMarkedForLateRender()
					&& obj->GetEnabled())
					obj->Render(camera);
			}

			Renderer::RenderDeferred();

			std::map<UString, Model*>& models = ResourceManager::LoadedModels();
			for (auto& model : models)
			{
				if (model.second)
					if (model.first != L"pointlight.obj"
						&& model.first != L"spotlight.obj")
						model.second->VRender(Time::DeltaTime(), Time::TotalTime(), camera);
			}

			//Render all lights in scene

			LightManager::RenderLights(camera);

			Renderer::RenderFinal();

			LightManager::ClearLights();

			//render all late render (UI) scene objects
			//NOTE: this is expensive, as we are iterating over the list of objects again...
			//      what should happen is the list should be sorted once, leaving all late render objects
			//      last to be drawn.
			for (int i = 0; i < m_topLevelObjects.size(); i++)
			{
				GameObject* obj = m_topLevelObjects.at(i);
				if (obj->IsMarkedForLateRender() && obj->GetEnabled())
					obj->Render(camera);
			}
		}

		LuaEngine::ExecuteExpression(VTEXT("collectgarbage()"));
	}

	GameObject* Scene::QueryObject(std::string name)
	{
		for (uint32_t i = 0; i < m_topLevelObjects.size(); i++)
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

	void Scene::SetMainCamera(ICamera3D* camera)
	{
		m_mainCamera = camera;
	}

	void Scene::AddCamera(ICamera3D* camera)
	{
		m_cameras.push_back(camera);
	}

	void Scene::RemoveCamera(ICamera3D* camera)
	{

		for (uint32_t i = 0; i < m_cameras.size(); i++)
		{
			if (m_cameras[i] == camera)
			{
				m_cameras.erase(m_cameras.begin() + i);
				return;
			}
		}
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

		Transform* transform = ParseTransform(element->FirstChildElement("transform"));

		const XMLElement* model = element->FirstChildElement("model");
		std::string modelFile = "";
		if (model)
		{
			modelFile = model->Attribute("file");
		}

		GameObject* _object = new GameObject(transform);
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

	Transform* Scene::ParseTransform(const tinyxml2::XMLElement* element)
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

	std::vector<Component*>
	Scene::ParseComponents(Scene* scene, const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		std::vector<Component*> components;

		const XMLElement* child = element->FirstChildElement();
		while (child)
		{
			std::string name(child->Name());
			Component* component = nullptr;
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
			else if (name == "pause-script")
			{
				component = ParsePauseScript(child);
			}
			else if (name == "fps-script")
			{
				component = ParseFpsScript(child);
			}
			else if (name == "mineshaft-script")
			{
				component = ParseMineshaftScript(child);
			}
			else if (name == "player-script")
			{
				component = ParsePlayerScript(child);
			}

			if (component)
				components.push_back(component);

			child = child->NextSiblingElement();
		}

		return components;
	}

	Component*
	Scene::ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		bool isMainCamera = element->BoolAttribute("mainCamera");
		Camera3DComponent* _camera = new Camera3DComponent();
		if (isMainCamera)
			scene->m_mainCamera = _camera->GetCamera();

		const XMLElement* _viewportElement = element->FirstChildElement("viewport");
		if (_viewportElement)
		{
			float x = _viewportElement->FloatAttribute("x");
			float y = _viewportElement->FloatAttribute("y");
			float w = _viewportElement->FloatAttribute("width");
			float h = _viewportElement->FloatAttribute("height");
			float minDepth = _viewportElement->FloatAttribute("min");
			float maxDepth = _viewportElement->FloatAttribute("max");

			Viewport v;
			v.xPercent = x;
			v.yPercent = y;
			v.wPercent = w;
			v.hPercent = h;
			v.x = x * Window::Width();         //x as percentage of Screen Width
			v.y = y * Window::Height();        //y as percentage of Screen Height
			v.width = w * Window::Width();     //width as percentage of Screen Width
			v.height = h * Window::Height();   //height as percentage of Screen Height
			v.minDepth = minDepth;
			v.maxDepth = maxDepth;
			v.sWidth = Window::Width();
			v.sHeight = Window::Height();

			_camera->GetCamera()->VSetViewport(v);
		}

		scene->AddCamera(_camera->GetCamera());
		return _camera;
	}

	Component* Scene::ParseLightComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		std::string type(element->Attribute("type"));
		if (type == "point")
		{

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
		else if (type == "spot")
		{

			SpotLightComponent* light = new SpotLightComponent;

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
				float angle = attenElement->FloatAttribute("angle");
				float constant = attenElement->FloatAttribute("constant");
				float linear = attenElement->FloatAttribute("linear");
				float quadratic = attenElement->FloatAttribute("quadratic");

				light->SetRange(range);
				light->SetConstant(constant);
				light->SetLinear(linear);
				light->SetQuadratic(quadratic);
				light->SetAngle(angle);

			}

			return light;
		}
		else if (type == "directional")
		{
			/*float dirX = element->FloatAttribute("dirX");
			float dirY = element->FloatAttribute("dirY");
			float dirZ = element->FloatAttribute("dirZ");
			light = new DirectionalLight;
			light->m_ambientColor = Vector3(red, green, blue);
			((DirectionalLight*)light)->m_direction = Vector3(dirX, dirY, dirZ);*/
		}
		else
		{
			/*light = new ILight;
			light->m_ambientColor = Vector3(red, green, blue);*/
		}

		return nullptr;
	}

	Component* Scene::ParseLuaScriptComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* scriptFile = element->Attribute("file");
		UString scriptPath = UStringFromCharArray(scriptFile);

		LuaScript* script = LuaScriptManager::LoadScript(scriptPath);
		return script;
	}

	Component* Scene::ParseUITextComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* text = element->Attribute("text");
		const char* font = element->Attribute("font");

		Font* _font = ResourceManager::OpenFont(UStringFromCharArray(font));
		_font->IncrementRefCount();

		UIText* _text = new UIText(UStringFromCharArray(text), _font);

		return _text;
	}

	Component* Scene::ParsePauseScript(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		PauseScript* script = new PauseScript;
		return script;
	}

	Component* Scene::ParseFpsScript(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		FpsScript* script = new FpsScript;
		return script;
	}

	Component* Scene::ParseMineshaftScript(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		MineshaftScript* script = new MineshaftScript;
		return script;
	}

	Component* Scene::ParsePlayerScript(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		PlayerScript* script = new PlayerScript;
		return script;
	}

	Component* Scene::ParseModelComponent(const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* file = element->Attribute("file");
		const char* materialFile = element->Attribute("material");

		Model* _model = ResourceManager::OpenModel(UStringFromCharArray(file));
		if (!_model)
		{
			DebugPrintF(VTEXT("Failed to open model.\n"));
			return NULL;
		}
		_model->IncrementRefCount();

		Material* _material = ResourceManager::OpenMaterial(UStringFromCharArray(materialFile));
		if (!_material)
		{
			DebugPrintF(VTEXT("Failed to open material.\n"));
			return NULL;
		}
		_material->IncrementRefCount();

		ModelComponent* _modelComponent = new ModelComponent;
		_modelComponent->SetModel(_model);
		_modelComponent->SetMaterial(_material);

		return _modelComponent;
	}
}

