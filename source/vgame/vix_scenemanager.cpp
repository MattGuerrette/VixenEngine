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

#include <vix_scenemanager.h>
#include <vix_stlutil.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_luaengine.h>
#include <vix_prefabmanager.h>
#include <vix_modelmanager.h>
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
        File* file = FileManager::OpenFile(PathManager::ScenePath() + VTEXT("scenes.config"));
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
                File* _sceneFile = FileManager::OpenFile(PathManager::ScenePath() + UStringFromCharArray(sceneFile));
                if (_sceneFile)
                {
                    Scene* scene = Scene::Deserialize(_sceneFile);
                    if (scene)
                        _manager.m_scenes[scene->GetID()] = scene;
                    FileManager::CloseFile(_sceneFile);
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

    void SceneManager::OpenScene(UString id)
    {
        SceneManager& _manager = SceneManager::instance();

        //attempt to find scene with id
        SceneMap::iterator it = _manager.m_scenes.find(id);
        if (it != _manager.m_scenes.end())
        {
            //make this scene the current
            _manager.m_current = it->second;
        }
        else
            DebugPrintF(VTEXT("SceneManager: scene %s not found\n"), id.c_str());
    }

    void SceneManager::UpdateScene()
    {
        SceneManager& _manager = SceneManager::instance();

        _manager.m_current->Update();


		PrefabManager::Cleanup();
    }

    void SceneManager::RenderScene()
    {
        SceneManager& _manager = SceneManager::instance();

        _manager.m_current->Render();
    }

	void SceneManager::PauseScene(UString id)
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

	void SceneManager::UnpauseScene(UString id)
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

}
