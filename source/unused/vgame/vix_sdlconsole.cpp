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
