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
#include <vix_version.h>

namespace Vixen {

	SDLGameWindow::SDLGameWindow(const SDL_GW_Params& params)
	{
		m_params = params;
		m_running = false;
		m_hidden = false;
		m_paused = false;
		m_fullscreen = false;
		m_cursorHidden = false;
		m_clientRect = Rect(0, 0, 0, 0);
        m_keyboardState = NULL;
        m_mouseState = NULL;
	}

	SDLGameWindow::~SDLGameWindow()
	{

	}

    void* SDLGameWindow::VNativeHandle()
    {
        return m_nativeHandle;
    }

	void SDLGameWindow::VToggleCursor()
	{
		m_cursorHidden = !m_cursorHidden;
		if(m_cursorHidden)
			SDL_ShowCursor(0);
		else
			SDL_ShowCursor(1);
	}

	void SDLGameWindow::VTogglePaused()
	{
		m_paused = !m_paused;
	}

	void SDLGameWindow::VTrapCursorCenter()
	{
		SDL_WarpMouseInWindow(m_windowHandle, VGetClientBounds().w/2, VGetClientBounds().h/2);
	}

	bool SDLGameWindow::VInit()
	{
		/* Initialize SDL
		*/
		if (SDL_Init(SDL_INIT_TIMER) != 0) {
			DebugPrintF(VTEXT("SDL Failed to Initialize"));
            return false;
		}

		/*Create the SDL_Window handle*/
#ifdef UNICODE
		UConverter convert;
		std::string title = convert.to_bytes(m_params.title) + " " + std::to_string(VixenEngine_VERSION_MAJOR) + "."
		                                                + std::to_string(VixenEngine_VERSION_MINOR) + "."
														+ std::to_string(VixenEngine_VERSION_BUILD);
#else
		std::string title = m_params.title + VTEXT(" ") + std::to_string(VixenEngine_VERSION_MAJOR) + VTEXT(".")
		                                                + std::to_string(VixenEngine_VERSION_MINOR) + VTEXT(".")
														+ std::to_string(VixenEngine_VERSION_BUILD);
#endif
		m_windowHandle = SDL_CreateWindow(title.c_str(),
											m_params.x <= 0 ? SDL_WINDOWPOS_CENTERED : m_params.x,
											m_params.y <= 0 ? SDL_WINDOWPOS_CENTERED : m_params.y,
											m_params.width,
											m_params.height,
											SDL_WINDOW_OPENGL);
		if (!m_windowHandle) {
			SDL_Quit();
			DebugPrintF(VTEXT("Failed to created SDL_Window handle"));
            return false;
		}

#ifdef VIX_SYS_WINDOWS
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);
        if (SDL_GetWindowWMInfo(m_windowHandle, &info))
        {
            m_nativeHandle = info.info.win.window;
        }
#endif

#ifdef VIX_SYS_LINUX //for now
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		/*create OpenGL context*/
		m_context = SDL_GL_CreateContext(m_windowHandle);
		if (!m_context) {
			SDL_Quit();
			DebugPrintF(VTEXT("Failed to create SDL_GL_Context handle"));
            return false;
		}
#endif
        m_mouseState = new SDLMouseState;
        m_keyboardState = new SDLKeyboardState;

<<<<<<< HEAD
		if (m_renderer){
			if(!m_renderer->VInitialize()) {
			  DebugPrintF(VTEXT("Renderer failed to initialize"));
				return false;
			}
		}
=======
        m_running = true;
>>>>>>> 5d61730afc80281f2da012a8e50084e490f8a879

		return true;
	}

    void SDLGameWindow::VPollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                VClose();
                break;

            case SDL_KEYDOWN:
                ((SDLKeyboardState*)m_keyboardState)->KeyDown(event.key.keysym.scancode);
                break;

            case SDL_KEYUP:
                ((SDLKeyboardState*)m_keyboardState)->KeyUp(event.key.keysym.scancode);
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                ((SDLMouseState*)m_mouseState)->MouseEvent(event.button);
                break;

            case SDL_MOUSEWHEEL:
                ((SDLMouseState*)m_mouseState)->MouseWheelEvent(event.wheel);
                break;

            case SDL_MOUSEMOTION:
                ((SDLMouseState*)m_mouseState)->MouseMove(event.motion.x, event.motion.y);
                break;
            }
        }
    }

	//bool SDLGameWindow::VRun()
	//{

	//	/*try and initialize window*/
	//	if (!VInit()) {
	//	  DebugPrintF(VTEXT("SDLGameWindow failed to initialize"));
	//		return false;
	//	}

	//	/*LOAD ONLY NECESSARY CONTENT FOR STARTUP*/
	//	m_parent->VOnStartup();


 //       Time::Start();
	//	//run application loop
	//	m_running = true;
	//	while (m_running)
	//	{

	//		Time::Tick();

	//		SDL_Event event;
	//		while (SDL_PollEvent(&event))
	//		{
	//			switch (event.type)
	//			{
	//			case SDL_QUIT:
	//				VClose();
	//				break;

	//			case SDL_KEYDOWN:
	//				((SDLKeyboardState*)Game::GetKeyboard())->KeyDown(event.key.keysym.scancode);
	//				break;

	//			case SDL_KEYUP:
	//				((SDLKeyboardState*)Game::GetKeyboard())->KeyUp(event.key.keysym.scancode);
	//				break;

	//			case SDL_MOUSEBUTTONDOWN:
	//			case SDL_MOUSEBUTTONUP:
	//				((SDLMouseState*)Game::GetMouse())->MouseEvent(event.button);
	//				break;

	//			case SDL_MOUSEWHEEL:
	//				((SDLMouseState*)Game::GetMouse())->MouseWheelEvent(event.wheel);
	//				break;

	//			case SDL_MOUSEMOTION:
 //                   ((SDLMouseState*)Game::GetMouse())->MouseMove(event.motion.x, event.motion.y);
	//				break;
	//			}
	//		}

	//		/*CLEAR BUFFERS*/
 //           if(m_renderer)
	//		    m_renderer->VClearBuffer(ClearArgs::COLOR_DEPTH_STENCIL_BUFFER);


	//		/*update*/
	//		m_parent->VOnUpdate();

	//		/*render*/
	//		m_parent->VOnRender();


	//		/*update keyboard state for next frame*/
	//		((SDLKeyboardState*)Game::GetKeyboard())->UpdatePrev();
	//		/*update mouse state for next frame*/
 //           ((SDLMouseState*)Game::GetMouse())->UpdatePrev();

	//		/*swap buffers*/
	//		VSwapBuffers();

	//		Time::CalculateFPS();
	//	}

	//	m_parent->VOnShutdown();

	//	return true;
	//}

    IKeyboardState* SDLGameWindow::VKeyboardState()
    {
        return m_keyboardState;
    }

    IMouseState* SDLGameWindow::VMouseState()
    {
        return m_mouseState;
    }

    void SDLGameWindow::VPollNextFrame()
    {
        /*update keyboard state for next frame*/
        ((SDLKeyboardState*)m_keyboardState)->UpdatePrev();
        /*update mouse state for next frame*/
        ((SDLMouseState*)m_mouseState)->UpdatePrev();
    }

	void SDLGameWindow::VSetFullscreen(bool flag)
	{
		m_fullscreen = flag;
		if (flag) {
			SDL_SetWindowFullscreen(m_windowHandle, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else {
			SDL_SetWindowFullscreen(m_windowHandle, 0);
		}
	}

	void SDLGameWindow::VSetVisible(bool flag)
	{


	}

    bool SDLGameWindow::VRunning()
    {
        return m_running;
    }

	void SDLGameWindow::VSwapBuffers()
	{
		SDL_GL_SwapWindow(m_windowHandle);
	}

    void SDLGameWindow::VSetTitle(std::string title)
    {
        SDL_SetWindowTitle(m_windowHandle, title.c_str());
    }

	const UString& SDLGameWindow::VGetTitle()
	{
		return m_title;
	}

	const Rect SDLGameWindow::VGetClientBounds()
	{
	    if(m_fullscreen) {
            SDL_GetWindowPosition(m_windowHandle, &m_clientRect.x, &m_clientRect.y);
            SDL_GetWindowSize(m_windowHandle, &m_clientRect.w, &m_clientRect.h);
	    }
		else {
            //we will take the requested size from config
            m_clientRect.w = m_params.width;
            m_clientRect.h = m_params.height;
        }

		return m_clientRect;
	}

	bool SDLGameWindow::VIsPaused()
	{
		return m_paused;
	}

	bool SDLGameWindow::VIsHidden()
	{
		return m_hidden;
	}

	bool SDLGameWindow::VIsRunning()
	{
		return m_running;
	}

	void SDLGameWindow::VClose()
	{
		m_running = false;
		SDL_GL_DeleteContext(m_context);
		SDL_Quit();
	}

	void SDLGameWindow::OutputDisplayModes()
	{
		int numModes = SDL_GetNumDisplayModes(0);
		for (int i = 0; i < numModes; i++)
		{
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, i, &mode);
			DebugPrintF(VTEXT("DisplayMode[%i]: <W: %i, H: %i>\n"), i, mode.w, mode.h);
		}
	}

}
