#include <vix_window_singleton.h>

namespace Vixen {

    bool Window::Initialize(const GameConfig& config)
    {
        Window& _window = Window::instance();

        _window.m_window = new SDLGameWindow(config.WindowArgs());
        bool success = _window.m_window->VInit();

        return success;
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
}
