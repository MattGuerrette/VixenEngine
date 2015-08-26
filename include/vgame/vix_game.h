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

#ifndef VIX_GAME_H
#define VIX_GAME_H

#include <vix_platform.h>
#include <vix_gamewindow.h>
#include <vix_gameconfig.h>

namespace Vixen {

	class VIX_API IGame
	{
	public:
		IGame();

		int Run();
		virtual void VOnStartup(void) = 0;
		virtual void VOnUpdate(float dt) = 0;
		virtual void VOnRender(float dt) = 0;
		virtual void VOnShutdown(void) = 0;

		IRenderer*			const GetRenderer() const;
		IGameWindow*		const GetWindow()   const;
		GameConfig*         const GetConfig()   const;
		SDLKeyboardState*	const GetKeyboard() const;
		SDLMouseState*		const GetMouse()	const;

	protected:
		GameConfig*			m_config;
		IGameWindow*		m_window;
		IRenderer*			m_renderer;
		SDLKeyboardState*	m_keyboard;
		SDLMouseState*      m_mouse;
	};

}

#endif
