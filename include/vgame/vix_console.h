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
