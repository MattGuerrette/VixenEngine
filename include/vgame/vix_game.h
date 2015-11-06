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

#ifndef VIX_GAME_H
#define VIX_GAME_H

#include <vix_platform.h>
#include <vix_gamewindow.h>
#include <vix_gameconfig.h>
#include <vix_resourceloader.h>
#include <vix_input.h>

namespace Vixen {


	class VIX_API Game
	{
	public:
		Game();

		int Run();

        static void Exit();

		/*virtual void VOnStartup(void) = 0;
		virtual void VOnUpdate(void) = 0;
		virtual void VOnRender(void) = 0;
		virtual void VOnShutdown(void) = 0;*/

		/*IRenderer*				const GetRenderer() const;
		GameWindow*			    const GetWindow()   const;
		GameConfig*				const GetConfig()   const;

		static IKeyboardState*	const GetKeyboard();
		static IMouseState*		const GetMouse();*/

	protected:
		/*GameConfig*				m_config;
		GameWindow*			    m_window;
		IRenderer*				m_renderer;
        IResourceLoader*		m_resourceLoader;*/

    private:
		/*static IKeyboardState*	s_keyboard;
		static IMouseState*	    s_mouse;*/
	};

}

#endif
