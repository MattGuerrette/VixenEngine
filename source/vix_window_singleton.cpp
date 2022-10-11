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

#include <vix_window_singleton.h>

namespace Vixen {

    bool Window::Initialize(const GameConfig& config)
    {
        Window& _window = Window::instance();

        _window.m_window = new SDLGameWindow(config.WindowArgs());
        if (!_window.m_window->VInit())
            return false;

        return true;
    }

    void Window::DeInitialize()
    {
        Window& _window = Window::instance();

        delete _window.m_window;
    }

    void* Window::Handle()
    {
        Window& _window = Window::instance();

        return _window.m_window->VNativeHandle();
    }

    bool Window::IsRunning()
    {
        Window& _window = Window::instance();

        return _window.m_window->VRunning();
    }

    void Window::SwapBuffers()
    {
        Window& _window = Window::instance();

        _window.m_window->VSwapBuffers();
    }


    void Window::PollInput()
    {
        Window& _window = Window::instance();

        _window.m_window->VPollEvents();
    }

    void Window::PollInputNextFrame()
    {
        Window& _window = Window::instance();

        _window.m_window->VPollNextFrame();
    }

    void Window::Close()
    {
        Window& _window = Window::instance();

        _window.m_window->VClose();
    }

    void Window::TrapCursorCenter()
    {
        Window& _window = Window::instance();

        _window.m_window->VTrapCursorCenter();
    }

    void Window::ToggleCursor()
    {
        Window& _window = Window::instance();

        _window.m_window->VToggleCursor();
    }

    uint32_t Window::Width()
    {
        Window& _window = Window::instance();

        return _window.m_window->VGetClientBounds().w;
    }

    uint32_t Window::Height()
    {
        Window& _window = Window::instance();

        return _window.m_window->VGetClientBounds().h;
    }

    IKeyboardState* Window::Keyboard()
    {
        Window& _window = Window::instance();

        return _window.m_window->VKeyboardState();
    }

    IMouseState* Window::Mouse()
    {
        Window& _window = Window::instance();

        return _window.m_window->VMouseState();
    }

    SDLControllerState * Window::Controller()
	{
		Window& _window = Window::instance();

		return _window.m_window->VControllerState();
	}

    void Window::StartTextCapture()
    {
        Window& _window = Window::instance();

        _window.m_window->VStartTextCapture();
    }

    std::string Window::InputBuffer()
    {
        Window& _window = Window::instance();

        return _window.m_window->VInputBuffer();
    }

    void Window::StopTextCapture()
    {
        Window& _window = Window::instance();

        _window.m_window->VStopTextCapture();
    }
}

