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
#include <vix_sdlwindow.h>
#include <vix_debugutil.h>
#include <vix_resourcemanager.h>
#include <vix_pathmanager.h>

#ifdef VIX_DIRECTX_BUILD
#include <vix_dxrenderer.h>
#include <vix_dxresourceloader.h>
#endif

#ifdef VIX_OPENGL_BUILD
#include <vix_glrenderer.h>
#endif

namespace Vixen {
	IKeyboardState* Game::s_keyboard = NULL;
    IMouseState*    Game::s_mouse = NULL;

	Game::Game()
	{
        FileManager::Initialize();
        PathManager::Initialize();

	    m_config = new GameConfig;
		m_window = new SDLGameWindow(m_config->WindowArgs());
#ifdef VIX_DIRECTX_BUILD
        m_renderer = new DXRenderer;
        m_resourceLoader = new DXResourceLoader((DXRenderer*)m_renderer);
#elif defined(VIX_OPENGL_BUILD)
        m_renderer = new GLRenderer;
#endif
		s_keyboard = new SDLKeyboardState;
		Input::SetKeyboardState(s_keyboard);
		s_mouse = new SDLMouseState;
        Input::SetMouseState(s_mouse);

		m_window->VSetParent(this);
		m_window->VSetRenderer(m_renderer);

        ResourceManager::AttachResourceLoader(m_resourceLoader);
	}

	int Game::Run()
	{
		/*if application window exists*/
		if (m_window) {
			if(!m_window->VRun()) {
			  DebugPrintF(VTEXT("Application loop encountered error"));
				return -1;
			}
		}

        m_renderer->VDeInitialize();

		return 0;
	}

	GameWindow* const Game::GetWindow() const
	{
		return m_window;
	}

	IRenderer* const Game::GetRenderer() const
	{
		return m_renderer;
	}

	GameConfig* const Game::GetConfig() const
	{
	    return m_config;
	}

	IKeyboardState* const Game::GetKeyboard()
	{
		return s_keyboard;
	}

	IMouseState* const Game::GetMouse()
	{
		return s_mouse;
	}



}
