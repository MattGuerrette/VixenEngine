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

#ifndef VIX_GL_TEXTURE_H
#define VIX_GL_TEXTURE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_texture.h>

namespace Vixen {

	VIX_API GLenum vixFIBmpToInternalFormat(FIBITMAP* bmp);
	VIX_API GLenum vixFIBmpToFormat(FIBITMAP* bmp);

	class VIX_API GLTexture : public ITexture
	{
		GLuint m_id;
		GLenum m_target;
		GLenum m_unit;

	public:
		GLTexture(GLenum target = GL_TEXTURE_2D);

		~GLTexture();

		void Bind(GLenum unit);

		void Unbind();

		bool VInitFromBMP(FREEIMAGE_BMP* bmp);
        bool VInitFromFile(File* file);

		size_t VGetWidth();
		size_t VGetHeight();

	private:
		size_t  m_width;
		size_t  m_height;
		int     m_uniqueID;
	};
}

#endif
