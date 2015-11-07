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

#ifndef VIX_GAMEWINDOW_H
#define VIX_GAMEWINDOW_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_stringutil.h>
#include <vix_rectangle.h>
#include <vix_renderer.h>
#include <vix_keyboardstate.h>
#include <vix_mousestate.h>

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

	};

}


#endif
