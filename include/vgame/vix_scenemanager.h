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

#ifndef VIX_SCENEMANAGER_H
#define VIX_SCENEMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_scene.h>
#include <vix_prefab.h>

namespace Vixen {

    class VIX_API SceneManager : public Singleton<SceneManager>
    {
        typedef std::map<std::string, Scene*> SceneMap;
		typedef std::map<std::string, std::string> SceneFileMap;
		typedef std::queue<Scene*> SceneQueue;
		typedef std::vector<Scene*> SceneList;
    public:

        static bool				Initialize();
        static void				DeInitialize();
		static Scene*				LoadScene(std::string fileName, bool initial = false);
        static void				OpenScene(std::string id);
		static void             AddScene(Scene* scene);
        static void				UpdateScenes();
		static void				RenderScenes();
		
        static GameObject*      AccessTopLevelObject(std::string id);
		static Scene*			ActiveScene();



		static void				ReloadScene(std::string sceneID);
		static void				PauseScene(std::string sceneID);
		static void				UnpauseScene(std::string sceneID);
		static void				HideScene(std::string sceneID);
		static void				ShowScene(std::string sceneID);
		static void				SetOrder(std::string sceneID, uint32_t order);

    private:
		SceneQueue m_sceneQueue;
        SceneMap   m_scenes;
		SceneFileMap m_sceneFiles;
		SceneList  m_sceneList;
        Scene*     m_current;
    };

}

#endif
