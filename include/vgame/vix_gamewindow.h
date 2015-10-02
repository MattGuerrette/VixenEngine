/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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

#ifndef VIX_GAMEWINDOW_H
#define VIX_GAMEWINDOW_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_stringutil.h>
#include <vix_rectangle.h>
#include <vix_renderer.h>

namespace Vixen {

	class Game;

	class VIX_API GameWindow : INonCopy
	{

	public:
		virtual ~GameWindow() { }

		virtual void               VSetParent(Game* game) = 0;
		virtual void               VSetRenderer(IRenderer* renderer) = 0;
		virtual bool               VInit() = 0;
		virtual bool               VRun() = 0;
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
        virtual void*              VNativeHandle() = 0;

        virtual float              VFPS() = 0;

		static const size_t DEF_WINDOW_WIDTH = 800;
		static const size_t DEF_WINDOW_HEIGHT = 600;

	protected:
		Game*               m_parent;
		IRenderer*          m_renderer;     
		UString				m_title;
		Rect                m_clientRect;
		bool				m_hidden;
		bool				m_running;
		bool				m_paused;
		bool                m_fullscreen;
		bool                m_cursorHidden;

	};

}


#endif
