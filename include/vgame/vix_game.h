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
