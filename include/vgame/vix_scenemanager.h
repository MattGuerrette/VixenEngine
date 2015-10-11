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
        typedef std::map<UString, Scene*> SceneMap;
    public:

        static bool				Initialize();
        static void				DeInitialize();
        static void				OpenScene(UString id);
		static void             AddScene(Scene* scene);
        static void				UpdateScene();
        static void				RenderScene();
		static void				PauseScene(UString id);
		static void				UnpauseScene(UString id);
        static GameObject*      AccessTopLevelObject(std::string id);
		static Scene*			ActiveScene();

    private:
        SceneMap   m_scenes;
        Scene*     m_current;
    };

}

#endif
