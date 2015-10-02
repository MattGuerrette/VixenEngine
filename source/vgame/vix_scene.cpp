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
#include <vix_modelmanager.h>
#include <vix_stlutil.h>
#include <vix_luascriptmanager.h>
#include <vix_luascript.h>
#include <vix_scenemanager.h>
#include <vix_objectmanager.h>
#include <vix_cameracomponent.h>

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
		if(m_topLevelObjects.size() > 0)
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

	void Scene::Update(float dt)
	{
		if (m_paused)
			return;

		//update all scene objects
		for(auto& object : m_topLevelObjects)
			if(object->GetEnabled())
				object->Update(dt);

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
        return _scene;
    }

	GameObject* Scene::ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		const char* objectName = element->Attribute("name");
		const bool enabled = element->BoolAttribute("enabled");
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

		const XMLElement* model = element->FirstChildElement("model");
        std::string modelFile = "";
        if (model) {
             modelFile = model->Attribute("file");
        }
		

		
		GameObject* _object = new GameObject(new Transform(posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ),
			ModelManager::AccessModel(UStringFromCharArray(modelFile.c_str())));
		_object->SetName(UStringFromCharArray(objectName));
		_object->SetEnabled(enabled, false);
		ObjectManager::MapSceneObject(_object);

        //PARSE CAMERA
        const XMLElement* camera = element->FirstChildElement("camera");
        if (camera)
        {
            bool isMainCamera = camera->BoolAttribute("mainCamera");

            if (isMainCamera)
            {
                CameraComponent* _camera = new CameraComponent;
                _camera->VBindParent(_object);
                _object->AddComponent(_camera);
                scene->m_mainCamera = _camera->GetCamera();
            }
            else {
                CameraComponent* _camera = new CameraComponent;
                _camera->VBindParent(_object);
                _object->AddComponent(_camera);
       
            }
        }

		//PARSE SCRIPTS
		const XMLElement* scripts = element->FirstChildElement("scripts");
		if (scripts)
		{
			const XMLElement* scriptNode = scripts->FirstChildElement("script");
			while (scriptNode != NULL)
			{
				const char* scriptFile = scriptNode->Attribute("file");
				UString scriptPath = UStringFromCharArray(scriptFile);

				LuaScript* _script = LuaScriptManager::LoadScript(scriptPath);
				_script->VBindParent(_object);
				_object->AddComponent(_script);


				scriptNode = scriptNode->NextSiblingElement("script");
			}
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
}