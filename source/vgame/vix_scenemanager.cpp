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

    void SceneManager::UpdateScene(float dt)
    {
        SceneManager& _manager = SceneManager::instance();

        _manager.m_current->Update(dt);

		LuaEngine::ExecuteExpression(VTEXT("collectgarbage()"));
		PrefabManager::Cleanup();
    }

    void SceneManager::RenderScene(float dt)
    {
        SceneManager& _manager = SceneManager::instance();

        _manager.m_current->Render(dt);
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

	Scene* SceneManager::ActiveScene()
	{
		SceneManager& _manager = SceneManager::instance();

		return _manager.m_current;
	}

}