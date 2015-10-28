#ifndef VIX_WINDOW_SINGLETON_H
#define VIX_WINDOW_SINGLETON_H

#include <vix_platform.h>
#include <vix_gameconfig.h>
#include <vix_gamewindow.h>

namespace Vixen {

    class VIX_API Window : public Singleton<Window>
    {
    public:
        static bool Initialize(const GameConfig& config);

        static void DeInitialize();

        static void* Handle();

        static bool  IsRunning();

        static void  PollInput();

        static void  SwapBuffers();

        static void  PollInputNextFrame();

        static void  Close();

        static IKeyboardState* Keyboard();
        
        static IMouseState*    Mouse();

    private:
        GameWindow*  m_window;
    };

}

#endif
