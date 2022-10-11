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

#ifndef VIX_GAMEWINDOW_H
#define VIX_GAMEWINDOW_H

#include "vix_platform.h"
#include "vix_noncopy.h"
#include "vix_stringutil.h"
#include "vix_rectangle.h"
#include "vix_renderer.h"
#include "vix_keyboardstate.h"
#include "vix_mousestate.h"

namespace Vixen {

	class Game;

	class SDLControllerState;

	class VIX_API GameWindow : INonCopy
	{

	public:
		virtual ~GameWindow() { }

		virtual bool               VInit() = 0;
		virtual void               VSetFullscreen(bool flag) = 0;
		virtual void               VSetVisible(bool flag) = 0;
		virtual void               VTogglePaused() = 0;
		virtual void               VSwapBuffers() = 0;
		virtual const UString&     VGetTitle() = 0;
		virtual const Rect         VGetClientBounds() = 0;
		virtual bool               VIsRunning() = 0;
		virtual bool               VIsPaused() = 0;
		virtual bool               VIsHidden() = 0;
		virtual void               VClose() = 0;
		virtual void               VToggleCursor() = 0;
		virtual void               VTrapCursorCenter() = 0;
        virtual void               VSetTitle(std::string title) = 0;
        virtual void*              VNativeHandle() = 0;
        virtual void               VPollEvents() = 0;
        virtual void               VPollNextFrame() = 0;
        virtual std::string        VInputBuffer() = 0;
        virtual void               VStartTextCapture() = 0;
        virtual void               VStopTextCapture() = 0;

        virtual bool               VRunning() = 0;

        virtual IKeyboardState*    VKeyboardState() = 0;
        virtual IMouseState*       VMouseState() = 0;
		virtual SDLControllerState* VControllerState() = 0;

		static const size_t DEF_WINDOW_WIDTH = 800;
		static const size_t DEF_WINDOW_HEIGHT = 600;

	protected:
		UString				m_title;
		Rect                m_clientRect;
        IKeyboardState*     m_keyboardState;
        IMouseState*        m_mouseState;
		SDLControllerState* m_controllerState;
		bool				m_hidden;
		bool				m_running;
		bool				m_paused;
		bool                m_fullscreen;
		bool                m_cursorHidden;
        bool                m_captureText;
        std::string         m_inputBuffer;
	};

}


#endif
