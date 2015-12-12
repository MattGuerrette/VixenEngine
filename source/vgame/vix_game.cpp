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

#include <vix_game.h>
#include <vix_debugutil.h>
#include <vix_resourcemanager.h>
#include <vix_pathmanager.h>
#include <vix_window_singleton.h>
#include <vix_renderer_singleton.h>
#include <vix_lightmanager.h>
#include <vix_objectmanager.h>
#include <vix_scenemanager.h>
#include <vix_luaengine.h>
#include <vix_luascriptmanager.h>
#include <vix_prefabmanager.h>
#include <vix_bulletsimulator.h>

namespace Vixen {

	Game::Game()
	{

	}

	int Game::Run()
	{
        FileManager::Initialize();
        PathManager::Initialize();
        if (!Window::Initialize(GameConfig()))
            return -1;

        if (!Renderer::Initialize(Window::Handle()))
            return -1;

        Input::SetMouseState(Window::Mouse());
        Input::SetKeyboardState(Window::Keyboard());
        Input::SetControllerState(Window::Controller());

        ResourceManager::Initialize();

        Renderer::InitializeSpriteBatch();
        ObjectManager::Initialize();
        LightManager::Initialize();
        LuaEngine::Initialize();
        LuaScriptManager::Initialize();
        BulletSimulator::Initialize(btVector3(0.0f, -10.0f, 0.0f));
        SceneManager::Initialize();



        Renderer::SetClearColor(Colors::Black);

        Time::Start();
        while (Window::IsRunning())
        {
            Time::Tick();

            Window::PollInput();

            Renderer::ClearBuffer(ClearArgs::COLOR_DEPTH_STENCIL_BUFFER);

            BulletSimulator::Step(Time::DeltaTime());

            SceneManager::UpdateScenes();

            SceneManager::RenderScenes();

            Renderer::SwapBuffers();

            Window::SwapBuffers();

            Window::PollInputNextFrame();

            Time::CalculateFPS();
        }

        SceneManager::DeInitialize();
        PrefabManager::Cleanup();

        BulletSimulator::DeInitialize();

        LuaEngine::DeInitialize();
        LightManager::DeInitialize();
        ObjectManager::DeInitialize();

        ResourceManager::DeInitialize();
        Renderer::DeInitialize();
        ResourceManager::PrintLoaded();

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
