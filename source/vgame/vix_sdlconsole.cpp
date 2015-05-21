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

#include <vix_sdlconsole.h>
#include <vix_glrenderer.h>

namespace Vixen{

	SDLConsole::SDLConsole()
	{
		m_offset = 0;
		m_visible = false;
	}

	SDLConsole::~SDLConsole()
	{

	}

	bool SDLConsole::IsActive()
	{
		return m_visible;
	}

	void SDLConsole::SetFont(BMFont* font)
	{
		m_font = font;
	}

	void SDLConsole::SetTexture(Texture* tex)
	{
		m_texture = tex;
	}

	void SDLConsole::Render(IRenderer* renderer, int x, int y)
	{
		if (!m_visible) //dont render unless visible
			return;

		if (!renderer || !m_texture || !m_font)
			return;

		USStream ss;
		ss << "<>: " << m_buffer.str();

		((GLRenderer*)renderer)->Render2DTexture((GLTexture*)m_texture,
			Vector2(x, y), Rect(0, 0, 0, 0), Vector2(0, 0), Vector2(1, 1), 0.0f, 1.0f, Colors::White, 0.0f);
		((GLRenderer*)renderer)->Render2DText(m_font, UString(ss.str().c_str()),
			Vector2(x+15, y+20), 1.0f, Colors::Snow);
	}

	void SDLConsole::Show()
	{
		m_visible = true;
	}

	void SDLConsole::Hide()
	{
		m_visible = false;
	}

	void SDLConsole::Toggle()
	{
		m_visible = !m_visible;
	}

	UString SDLConsole::Buffer()
	{
		return m_buffer.str();
	}

	void SDLConsole::Write(const char* text, size_t len)
	{
		/*limit buffer write to MAX_COMMAND_LEN*/
		if (m_offset + len < 64)
		{
			m_buffer << text;
			m_offset += len;
		}
	}

	void SDLConsole::Erase(size_t len)
	{
		/*erase everything*/
		if (len == -1) {
			m_buffer.str(VTEXT(""));
			m_buffer.clear();
			m_offset = 0;
			return;
		}

		/*kinda gross, a lot of copying but o well....*/
		UString temp = m_buffer.str();
		size_t end = temp.length();
		if (end != 0)
			temp = temp.erase(end - len);
		else
			return;
		m_buffer.str(VTEXT(""));
		m_buffer.clear();
		m_buffer << temp;
		m_offset = 0;
		m_offset = m_buffer.str().length();
	}
}
