#include <vix_window_singleton.h>

namespace Vixen {

    bool Window::Initialize(const GameConfig& config)
    {
        Window& _window = Window::instance();

        _window.m_window = new SDLGameWindow(config.WindowArgs());
        if (!_window.m_window->VInit())
            return false;
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
}