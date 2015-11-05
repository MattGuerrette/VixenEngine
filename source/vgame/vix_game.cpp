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

#include <vix_game.h>
#include <vix_debugutil.h>
#include <vix_resourcemanager.h>
#include <vix_pathmanager.h>
#include <vix_window_singleton.h>
#include <vix_renderer_singleton.h>
#include <vix_objectmanager.h>
#include <vix_scenemanager.h>
#include <vix_luaengine.h>
#include <vix_luascriptmanager.h>
#include <vix_modelmanager.h>
#include <vix_prefabmanager.h>

namespace Vixen {

	Game::Game()
	{
      
	}

	int Game::Run()
	{
        FileManager::Initialize();
        PathManager::Initialize();
        if(!Window::Initialize(GameConfig()))
            return -1;

        if (!Renderer::Initialize(Window::Handle()))
            return -1;

        Input::SetMouseState(Window::Mouse());
        Input::SetKeyboardState(Window::Keyboard());

        ResourceManager::Initialize();
        Renderer::InitializeSpriteBatch();
        ObjectManager::Initialize();
        LuaEngine::Initialize();
        LuaScriptManager::Initialize();
        //ModelManager::Initialize();
        SceneManager::Initialize();

        Renderer::SetClearColor(Colors::Black);

        Time::Start();
        while (Window::IsRunning())
        {
            Time::Tick();

            Window::PollInput();

            Renderer::ClearBuffer(ClearArgs::COLOR_DEPTH_STENCIL_BUFFER);

            SceneManager::UpdateScenes();

            SceneManager::RenderScenes();

            Renderer::SwapBuffers();

            Window::SwapBuffers();

            Window::PollInputNextFrame();

            Time::CalculateFPS();
        }

		SceneManager::DeInitialize();
		PrefabManager::Cleanup();
        
        ModelManager::DeInitialize();
        LuaEngine::DeInitialize();
        ObjectManager::DeInitialize();
        ResourceManager::DeInitialize();
        Renderer::DeInitialize();
        Window::DeInitialize();
        PathManager::DeInitialize();
        FileManager::DeInitialize();


		return 0;
	}


    void Game::Exit()
    {
        Window::Close();
    }

}
