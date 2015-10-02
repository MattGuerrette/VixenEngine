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

	Renderer* const Game::GetRenderer() const
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
