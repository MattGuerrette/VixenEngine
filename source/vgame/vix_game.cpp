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

#include <vix_game.h>
#include <vix_debugutil.h>
#include <vix_resourcemanager.h>
#include <vix_pathmanager.h>
#include <vix_window_singleton.h>
#include <vix_renderer_singleton.h>
#include <vix_objectmanager.h>
#include <vix_scenemanager.h>
#include <vix_modelmanager.h>

namespace Vixen {

	Game::Game()
	{

	}

	int Game::Run()
	{
        FileManager::Initialize();
        PathManager::Initialize();
		GameConfig* cfg = new GameConfig();
        bool success = Window::Initialize(*cfg);
        if(!success)
			return -1;
		delete cfg;

        success = Renderer::Initialize(Window::Handle());
		if(!success)
			return -1;

        Input::SetMouseState(Window::Mouse());
        Input::SetKeyboardState(Window::Keyboard());

        ResourceManager::Initialize();
        Renderer::InitializeSpriteBatch();
        //ObjectManager::Initialize();
        //ModelManager::Initialize();
        //SceneManager::Initialize();

        Renderer::SetClearColor(Colors::Black);

        Time::Start();
        while (Window::IsRunning())
        {
            Time::Tick();

            Window::PollInput();

            Renderer::ClearBuffer(ClearArgs::COLOR_DEPTH_STENCIL_BUFFER);

            //SceneManager::UpdateScenes();

            //SceneManager::RenderScenes();

            Renderer::SwapBuffers();

            Window::SwapBuffers();

            Window::PollInputNextFrame();

            Time::CalculateFPS();
        }

        //SceneManager::DeInitialize();
        //ModelManager::DeInitialize();
        //ObjectManager::DeInitialize();
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
