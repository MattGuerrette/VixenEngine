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

#include <vix_scenemanager.h>
#include <vix_stlutil.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_luaengine.h>
#include <vix_prefabmanager.h>
#include <vix_luascript.h>
#include <vix_luascriptmanager.h>

namespace Vixen {

	/////////////////////////////////////////////////////////
	// SceneManager implementation
	/////////////////////////////////////////////////////////

    bool SceneManager::Initialize()
    {
        SceneManager& _manager = SceneManager::instance();

        using namespace tinyxml2;

        //need to attempt to open scene list
        File* file = FileManager::OpenFile(PathManager::ScenePath() + VTEXT("scenes.config"), FileMode::ReadBinary);
        if (file) {

            //File is actually an XML file
            //we should now open for reading
            XMLDOC document;
            XMLError err = document.LoadFile(file->Handle());
            UString errString;
            if (XMLErrCheck(err, errString))
            {
                DebugPrintF(VTEXT("Scene Config File failed to load\n"));
                FileManager::CloseFile(file);
                return false;
            }

            const XMLElement* sceneList = document.FirstChildElement("scenes");
            const XMLElement* sceneNode = sceneList->FirstChildElement("scene");
            while (sceneNode != NULL)
            {
                const char* sceneFile = sceneNode->Attribute("file");
				bool initial = sceneNode->BoolAttribute("initial");

				Scene* scene = _manager.LoadScene(sceneFile, initial);
				if (scene) {
					DebugPrintF(VTEXT("SceneManager: loaded scene %s successfully \n"), sceneFile);
				}
				else {
					DebugPrintF(VTEXT("SceneManager: scene %s not found\n"), sceneFile);
				}
                sceneNode = sceneNode->NextSiblingElement("scene");
            }
            FileManager::CloseFile(file);
            return true;
        }

        FileManager::CloseFile(file);
        return false;
    }

	void SceneManager::AddScene(Scene* scene)
	{
		SceneManager& _manager = SceneManager::instance();

		_manager.m_current = scene;
	}

    void SceneManager::DeInitialize()
    {
		LuaEngine::ExecuteExpression(VTEXT("collectgarbage()"));
        STLMAP_DELETE(SceneManager::instance().m_scenes);
    }

	void SceneManager::SetOrder(std::string sceneID, uint32_t order)
	{
		SceneManager& _manager = SceneManager::instance();

		//attempt to find scene with id
		SceneMap::iterator it = _manager.m_scenes.find(sceneID);
		if (it != _manager.m_scenes.end())
		{
			Scene* _scene = it->second;
			if (_scene) {
				for (int32_t i = 0; i < _manager.m_sceneList.size(); i++) {
					if (_scene == _manager.m_sceneList[i]) {
						_manager.m_sceneList.erase(_manager.m_sceneList.begin() + i);
						_manager.m_sceneList.insert(_manager.m_sceneList.begin() + order, _scene);
						return;
					}
				}
			}
		}
	}

    void SceneManager::UpdateCameraViewports(uint32_t width, uint32_t height)
    {
        SceneManager& _manager = SceneManager::instance();

        Scene* _scene = _manager.ActiveScene();
        if (_scene)
        {
            for (uint32_t i = 0; i < _scene->m_cameras.size(); i++)
            {
                ICamera3D* camera = _scene->m_cameras[i];
                if (camera)
                {
                    Viewport v = camera->VGetViewport();
                    v.x = v.xPercent * width;
                    v.y = v.yPercent * height;
                    v.width = v.wPercent * width;
                    v.height = v.hPercent * height;
                    v.sWidth = width;
                    v.sHeight = height;

                    camera->VSetViewport(v);
                }
            }
        }
    }

	Scene* SceneManager::LoadScene(std::string fileName, bool initial)
	{
		SceneManager& _manager = SceneManager::instance();

		File* sceneFile = FileManager::OpenFile(PathManager::ScenePath() + UStringFromCharArray(fileName.c_str()), FileMode::ReadBinary);
		if (sceneFile)
		{
			Scene* scene = Scene::Deserialize(sceneFile);
			if (scene) {
				scene->SetFileName(fileName);

				_manager.m_sceneFiles[scene->GetID()] = scene->GetFileName();
				_manager.m_scenes[scene->GetID()] = scene;

				if (initial) {
					_manager.m_sceneList.push_back(scene);
					_manager.m_current = scene;
				}
				return scene;
			}

			FileManager::CloseFile(sceneFile);
		}
		return nullptr;
	}

    void SceneManager::OpenScene(std::string id)
    {
        SceneManager& _manager = SceneManager::instance();

        //attempt to find scene with id
        SceneMap::iterator it = _manager.m_scenes.find(id);
        if (it == _manager.m_scenes.end())
		{
			SceneFileMap::iterator itt = _manager.m_sceneFiles.find(id);
			if (itt == _manager.m_sceneFiles.end())
			{
				DebugPrintF(VTEXT("SceneManager: scene %s not found\n"), id.c_str());
			}
			else {
				std::string fileName = itt->second;
				Scene* scene = _manager.LoadScene(fileName);
				_manager.m_sceneList.push_back(scene);
			}
		}
		else {
			Scene* scene = it->second;
			_manager.m_sceneList.push_back(scene);
		}

    }

    void SceneManager::UpdateScenes()
    {
        SceneManager& _manager = SceneManager::instance();

		for (int32_t i = 0; i < _manager.m_sceneList.size(); i++)
		{
			Scene* _scene = _manager.m_sceneList[i];
			_manager.m_current = _scene;
			if (_scene && !_scene->IsPaused())
				_scene->Update();
		}
        //_manager.m_current->Update();


		PrefabManager::Cleanup();
    }

    void SceneManager::RenderScenes()
    {
        SceneManager& _manager = SceneManager::instance();


		for (int32_t i = 0; i < _manager.m_sceneList.size(); i++)
		{
			Scene* _scene = _manager.m_sceneList[i];
			if (_scene && !_scene->IsHidden())
				_scene->Render();
		}
        //_manager.m_current->Render();
    }

	void SceneManager::PauseScene(std::string id)
	{
		SceneManager& _manager = SceneManager::instance();

		//attempt to find scene with id
		SceneMap::iterator it = _manager.m_scenes.find(id);
		if (it != _manager.m_scenes.end())
		{
			//make this scene the current
			it->second->SetPaused(true);
		}
	}

	void SceneManager::UnpauseScene(std::string id)
	{
		SceneManager& _manager = SceneManager::instance();

		//attempt to find scene with id
		SceneMap::iterator it = _manager.m_scenes.find(id);
		if (it != _manager.m_scenes.end())
		{
			//make this scene the current
			it->second->SetPaused(false);
		}
	}

    GameObject* SceneManager::AccessTopLevelObject(std::string id)
    {
        Scene* activeScene = SceneManager::ActiveScene();
        if (activeScene)
        {
            return activeScene->QueryObject(id);
        }
    }

	Scene* SceneManager::ActiveScene()
	{
		SceneManager& _manager = SceneManager::instance();

		return _manager.m_current;
	}

	void SceneManager::HideScene(std::string id)
	{
		SceneManager& _manager = SceneManager::instance();

		SceneMap::iterator it = _manager.m_scenes.find(id);
		if (it != _manager.m_scenes.end())
		{
			it->second->SetHidden(true);
		}
	}

	void SceneManager::ShowScene(std::string id)
	{
		SceneManager& _manager = SceneManager::instance();

		SceneMap::iterator it = _manager.m_scenes.find(id);
		if (it != _manager.m_scenes.end())
		{
			it->second->SetHidden(false);
		}
	}


	void SceneManager::ReloadScene(std::string sceneID)
	{
		SceneManager& _manager = SceneManager::instance();

		for (int32_t i = 0; i < _manager.m_sceneList.size(); i++)
		{
			Scene* _scene = _manager.m_sceneList[i];
			if (_scene)
			{
				if (_scene->GetID() == sceneID)
				{
					std::string sceneFile = _scene->GetFileName();

					_manager.m_sceneList.erase(_manager.m_sceneList.begin() + i);
					delete _scene;

					_scene = _manager.LoadScene(sceneFile);
					_manager.m_sceneList.push_back(_scene);
					return;
				}
			}
		}
	}
}
