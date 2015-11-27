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

#ifndef VIX_SDLCONSOLE_H
#define VIX_SDLCONSOLE_H

#include <vix_platform.h>
#include <vix_console.h>

namespace Vixen {

	class VIX_API SDLConsole : public IConsole
	{
	public:
		SDLConsole();

		~SDLConsole();

		bool    IsActive();
		void    Toggle();
		void    Show();
		void    Hide();
		UString Buffer();
		void	Write(const char* text, size_t len);
		void	Erase(size_t len);
		void    Render(IRenderer* renderer, int x, int y);
		void    SetFont(BMFont* font);
		void    SetTexture(Texture* tex);

	};
}

#endif
