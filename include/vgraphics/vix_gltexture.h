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

		GLTexture(const UString& filePath, GLenum target = GL_TEXTURE_2D);

		~GLTexture();

		void Bind(GLenum unit);

		void Unbind();

		ErrCode InitFromFile(const UString& filePath);
		ErrCode InitFromFIBMP(FREEIMAGE_BMP* bitmap);
	};
}

#endif
