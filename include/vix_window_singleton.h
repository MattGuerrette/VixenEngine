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

#ifndef VIX_WINDOW_SINGLETON_H
#define VIX_WINDOW_SINGLETON_H

#include "vix_platform.h"
#include "vix_gameconfig.h"
#include "vix_gamewindow.h"

namespace Vixen {

    class VIX_API Window : public Singleton<Window>
    {
    public:
        static bool             Initialize(const GameConfig& config);

        static void             DeInitialize();

        static void*            Handle();

        static bool             IsRunning();

        static void             PollInput();

        static void             SwapBuffers();

        static void             PollInputNextFrame();

        static void             TrapCursorCenter();

        static void             ToggleCursor();

        static void             Close();

        static IKeyboardState*  Keyboard();

        static IMouseState*     Mouse();

		static SDLControllerState*     Controller();

        static uint32_t         Width();

        static uint32_t         Height();

        static void             StartTextCapture();

        static std::string      InputBuffer();

        static void             StopTextCapture();

    private:
        GameWindow*  m_window;
    };

}

#endif
