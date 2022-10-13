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
#include <vix_sdlwindow.h>
#include "vix_debugutil.h"
#include "vix_renderer_singleton.h"
#include <vix_scenemanager.h>

namespace Vixen {

	SDLGameWindow::SDLGameWindow(const SDL_GW_Params& params)
	{
		m_params = params;
		m_running = false;
		m_hidden = false;
		m_paused = false;
		m_fullscreen = false;
		m_cursorHidden = false;
        m_captureText = false;
		m_clientRect = Rect(0, 0, 0, 0);
        m_keyboardState = NULL;
        m_mouseState = NULL;
		for (int i = 0; i < 4; i++)
		{
			m_controllerIndeces[i] = -1;
		}
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
		if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
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
                                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
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
		m_controllerState = new SDLControllerState;
        m_running = true;

		return true;
	}

    void SDLGameWindow::VPollEvents()
    {
		/*std::stringstream ss;
		ss << "FPS: " << Time::FPS();
		SDL_SetWindowTitle(m_windowHandle, ss.str().c_str());*/

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
			switch (event.type)
			{
				case SDL_QUIT:
					VClose();
					break;

				case SDL_KEYDOWN:
                {
                    ((SDLKeyboardState*)m_keyboardState)->KeyDown(event.key.keysym.scancode);

                    if (m_captureText && event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                    {
                        if(m_inputBuffer.size() > 0)
                            m_inputBuffer.pop_back();
                    }

                } break;

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
				case SDL_CONTROLLERDEVICEADDED:
					{
						for (int i = 0; i < 4; i++)
						{
							if (m_controllerIndeces[i] == -1)
							{
								m_controllers[i] = SDL_GameControllerOpen(event.cdevice.which);
								m_controllerIndeces[i] = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_controllers[i]));
								m_controllerState->Connected(true, i);
								break;
							}
						}
					}
					break;
				case SDL_CONTROLLERDEVICEREMOVED:
					{
						int cont = GetPlayerFromControllerIndex(event.cdevice.which);
						SDL_GameControllerClose(m_controllers[cont]);
						m_controllerState->Connected(false, cont);
						m_controllerIndeces[cont] = -1;
					}
					break;
				case SDL_CONTROLLERBUTTONDOWN:
					m_controllerState->ButtonDown((SDL_GameControllerButton)event.cbutton.button, GetPlayerFromControllerIndex(event.cdevice.which));
					break;
				case SDL_CONTROLLERBUTTONUP:
					m_controllerState->ButtonUp((SDL_GameControllerButton)event.cbutton.button, GetPlayerFromControllerIndex(event.cdevice.which));
					break;
				case SDL_CONTROLLERAXISMOTION:
					m_controllerState->Axis((SDL_GameControllerAxis)event.caxis.axis, event.caxis.value, GetPlayerFromControllerIndex(event.cdevice.which));
					break;

                case SDL_TEXTINPUT:
                    m_inputBuffer += event.text.text;
                    break;


                //HANDLE SDL WINDOW EVENTS
                case SDL_WINDOWEVENT:
                {
                    switch (event.window.event)
                    {
                    case SDL_WINDOWEVENT_SHOWN:

                    case SDL_WINDOWEVENT_HIDDEN:
                    case SDL_WINDOWEVENT_EXPOSED:
                    case SDL_WINDOWEVENT_MOVED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                    case SDL_WINDOWEVENT_MINIMIZED:
                    case SDL_WINDOWEVENT_MAXIMIZED:
                    case SDL_WINDOWEVENT_RESTORED:
                    case SDL_WINDOWEVENT_ENTER:
                    case SDL_WINDOWEVENT_LEAVE:
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    case SDL_WINDOWEVENT_CLOSE:
                        break;


                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        //HANDLE WINDOW RESIZE
                        Renderer::ResizeBuffers(event.window.data1, event.window.data2);

                        SceneManager::UpdateCameraViewports(event.window.data1, event.window.data2);
                    } break;

                    default:
                        break;
                    }

                } break;
            }
        }
    }

    void SDLGameWindow::VStartTextCapture()
    {
        m_captureText = true;
        SDL_StartTextInput();
    }

    std::string SDLGameWindow::VInputBuffer()
    {
        return m_inputBuffer;
    }

    void SDLGameWindow::VStopTextCapture()
    {
        m_captureText = false;
        SDL_StopTextInput();
        m_inputBuffer.clear();
    }

    IKeyboardState* SDLGameWindow::VKeyboardState()
    {
        return m_keyboardState;
    }

    IMouseState* SDLGameWindow::VMouseState()
    {
        return m_mouseState;
    }

	SDLControllerState * SDLGameWindow::VControllerState()
	{
		return m_controllerState;
	}

    void SDLGameWindow::VPollNextFrame()
    {
        /*update keyboard state for next frame*/
        ((SDLKeyboardState*)m_keyboardState)->UpdatePrev();
        /*update mouse state for next frame*/
        ((SDLMouseState*)m_mouseState)->UpdatePrev();
		/*update mouse state for next frame*/
		(m_controllerState)->UpdatePrev();
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

	int SDLGameWindow::GetPlayerFromControllerIndex(int controllerIndex)
	{
		for (int i = 0; i < 4; i++) {
			if (m_controllerIndeces[i] == controllerIndex)
			 	return i;
		}

		return 0;
	}

}
