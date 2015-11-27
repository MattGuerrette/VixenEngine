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


#include <vix_gltexture.h>
#include <vix_debugutil.h>
#include <vix_fileutil.h>

namespace Vixen {

	//NOTE:
	//
	//	Clearly there are more internal formats, and the formats
	//  for images depend on their compression type, bits, etc.
	//  Eventually this should take all that into account
	//
	GLenum vixFIBmpToInternalFormat(FIBITMAP* bmp)
	{
		GLenum format = GL_NONE;

		size_t bpp = FreeImage_GetBPP(bmp);
		switch (bpp)
		{
		case 24:
			format = GL_RGB8;
			break;
		case 32:
			format = GL_RGBA8;
			break;
		}

		return format;
	}

	//NOTE:
	//
	//	Clearly there are more formats, and the formats
	//  for images depend on their compression type, bits, etc.
	//  Eventually this should take all that into account
	//
	GLenum vixFIBmpToFormat(FIBITMAP* bmp)
	{
		GLenum format = GL_NONE;

		size_t bpp = FreeImage_GetBPP(bmp);
		switch (bpp)
		{
		case 24:
			format = GL_BGR;
			break;
		case 32:
			format = GL_BGRA;
			break;
		}

		return format;
	}

	GLTexture::GLTexture(GLenum target /* = GL_TEXTURE_2D */)
	{
		m_width = 0;
		m_height = 0;
		m_target = target;
	}

	GLTexture::~GLTexture()
	{
		//unload opengl generated texture
		glDeleteTextures(1, &m_id);
	}

	void GLTexture::Bind(GLenum unit)
	{
		m_unit = unit;
		glActiveTexture(unit);
		glBindTexture(m_target, m_id);

		/*DONT USE THIS FUNCTION*/
		/*glBindMultiTextureEXT(m_unit, m_target, m_id);*/
	}

	void GLTexture::Unbind()
	{
		glBindTexture(m_target, 0);
	}


	bool GLTexture::VInitFromFile(File* file)
	{
		return true;
	}

	bool GLTexture::VInitFromBMP(FREEIMAGE_BMP* bitmap)
	{

		//store width and height
		m_width = bitmap->header.width;
		m_height = bitmap->header.height;

		//now that we have our image data, create opengl texture handle
		glGenTextures(1, &m_id);
		m_uniqueID = m_id; //store gl texture id as unique id

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//bind opengl texture handle
		glBindTexture(m_target, m_id);



		//retrieve internal format
		GLenum internalFormat = vixFIBmpToInternalFormat(bitmap->bitmap);
		//retrieve format
		GLenum format = vixFIBmpToFormat(bitmap->bitmap);
		glTexImage2D(m_target, 0, internalFormat, bitmap->header.width, bitmap->header.height, 0, format, GL_UNSIGNED_BYTE, bitmap->data);
		glGenerateMipmap(m_target);
		glTexParameterf(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


		return true;
	}

}
