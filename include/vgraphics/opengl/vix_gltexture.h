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

#ifndef VIX_GL_TEXTURE_H
#define VIX_GL_TEXTURE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_texture.h>

namespace Vixen {

	VIX_API GLenum vixFIBmpToInternalFormat(FIBITMAP* bmp);
	VIX_API GLenum vixFIBmpToFormat(FIBITMAP* bmp);

	class VIX_API GLTexture : public Texture
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
