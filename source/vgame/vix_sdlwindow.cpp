/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

namespace Vixen {

	SDLGameWindow::SDLGameWindow(const SDL_GW_Params& params)
	{
		m_params = params;
		m_running = false;
		m_hidden = false;
		m_paused = false;
		m_fullscreen = false;
		m_parent = NULL;
		m_renderer = NULL;
		m_cursorHidden = false;
		m_clientRect = Rect(0, 0, 0, 0);
	}

	SDLGameWindow::~SDLGameWindow()
	{

	}

	void SDLGameWindow::VSetParent(IGame* game)
	{
		m_parent = game;
	}

    void* SDLGameWindow::VNativeHandle()
    {
        return m_nativeHandle;
    }

	SDLTimer* SDLGameWindow::Timer()
	{
		return &m_timer;
	}

	void SDLGameWindow::VSetRenderer(IRenderer* renderer)
	{
		m_renderer = renderer;
	}

	void SDLGameWindow::VToggleCursor()
	{
		m_cursorHidden = !m_cursorHidden;
		if(m_cursorHidden)
			SDL_ShowCursor(0);
		else
			SDL_ShowCursor(1);
	}

	void SDLGameWindow::VTrapCursorCenter()
	{
		SDL_WarpMouseInWindow(m_windowHandle, m_clientRect.w/2, m_clientRect.h/2);
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
		std::string title = convert.to_bytes(m_params.title);
#else
		std::string title = m_params.title;
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
            if (m_renderer)
                m_renderer->VAttachNativeHandle(m_nativeHandle);
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

		if (m_renderer && !m_renderer->VInitialize()) {
		  DebugPrintF(VTEXT("Renderer failed to initialize"));
			return false;
		}

		return true;
	}

	bool SDLGameWindow::VRun()
	{

		/*try and initialize window*/
		if (!VInit()) {
		  DebugPrintF(VTEXT("SDLGameWindow failed to initialize"));
			return false;
		}

		/*LOAD ONLY NECESSARY CONTENT FOR STARTUP*/
		m_parent->VOnStartup();


        m_timer.Start();
		//run application loop
		m_running = true;
		while (m_running)
		{

            m_timer.Tick();

			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					VClose();
					break;

				case SDL_KEYDOWN:
					m_parent->GetKeyboard()->KeyDown(event.key.keysym.scancode);
					break;

				case SDL_KEYUP:
					m_parent->GetKeyboard()->KeyUp(event.key.keysym.scancode);
					break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					m_parent->GetMouse()->MouseEvent(event.button);
					break;

				case SDL_MOUSEMOTION:
					m_parent->GetMouse()->MouseMove(event.motion.x, event.motion.y);
					break;
				}
			}

			/*CLEAR BUFFERS*/
            if(m_renderer)
			    m_renderer->VClearBuffer(ClearArgs::COLOR_DEPTH_STENCIL_BUFFER);

			/*update*/
			m_parent->VOnUpdate(m_timer.DeltaTime());

			/*render*/
			m_parent->VOnRender(m_timer.DeltaTime());

			/*update keyboard state for next frame*/
			m_parent->GetKeyboard()->UpdatePrev();
			/*update mouse state for next frame*/
			m_parent->GetMouse()->UpdatePrev();

			/*swap buffers*/
			VSwapBuffers();

			m_timer.CalculateFPS();
		}

		m_parent->VOnShutdown();

		return true;
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

	void SDLGameWindow::VSwapBuffers()
	{
        if (m_renderer->Type() == IRenderer::RendererType::DIRECTX)
            m_renderer->VSwapBuffers();
        else
            SDL_GL_SwapWindow(m_windowHandle);
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
            m_clientRect.w = m_parent->GetConfig()->WindowArgs().width;
            m_clientRect.h = m_parent->GetConfig()->WindowArgs().height;
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
