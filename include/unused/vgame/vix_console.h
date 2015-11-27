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

#ifndef VIX_CONSOLE_H
#define VIX_CONSOLE_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_renderer.h>
#include <vix_bmfont.h>
#include <vix_texture.h>

namespace Vixen {

	class VIX_API IConsole : public INonCopy
	{
	public:
		virtual ~IConsole() { }

		virtual bool    IsActive(void) = 0;
		virtual void    Toggle(void) = 0;
		virtual void    Show(void) = 0;
		virtual void    Hide(void) = 0;
		virtual UString Buffer(void) = 0;
		virtual void	Write(const char* text, size_t len) = 0;
		virtual void	Erase(size_t len) = 0;
		virtual void    Render(IRenderer* renderer, int x, int y) = 0;
		virtual void    SetFont(BMFont* font) = 0;
		virtual void    SetTexture(Texture* tex) = 0;

	protected:
		USStream  m_buffer;
		int       m_offset;
		bool      m_visible;
		BMFont*   m_font;
		Texture*  m_texture;
	};
}

#endif
