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
		typedef std::vector<Scene*> SceneList;
    public:
       
        static bool				Initialize();
        static void				DeInitialize();
		static bool				LoadScene(std::string fileName, std::string id = "", bool initial = false);
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
        SceneMap   m_scenes;
		SceneList  m_sceneList;
        Scene*     m_current;
    };

}

#endif