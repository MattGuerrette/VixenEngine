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

        static void             UpdateCameraViewports(uint32_t width, uint32_t height);

    private:
		SceneQueue m_sceneQueue;
        SceneMap   m_scenes;
		SceneFileMap m_sceneFiles;
		SceneList  m_sceneList;
        Scene*     m_current;

    };

}

#endif
