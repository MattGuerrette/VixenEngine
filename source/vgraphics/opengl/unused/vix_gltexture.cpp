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

	GLTexture::GLTexture(const UString& filePath, GLenum target /* = GL_TEXTURE_2D */)
	{
		m_width = 0;
		m_height = 0;
		m_target = target;

		ErrCode error = InitFromFile(filePath);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Texture failed to initialize"));
		}
	}

	GLTexture::GLTexture(FREEIMAGE_BMP* bmp, GLenum target /* = GL_TEXTURE_2D */)
	{
		m_width = 0;
		m_height = 0;
		m_target = target;

		ErrCode error = InitFromFIBMP(bmp);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Texture failed to initialize"));
		}
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
		glBindTexture(m_target, NULL);
	}


	ErrCode GLTexture::InitFromFile(const UString& filePath)
	{
		//pointer to image data
		FREEIMAGE_BMP* image = NULL;

		/*set texture name*/
		m_name = getFileName(filePath);

		//try and load the buffer with data
		image = FREEIMAGE_LoadImage(filePath);
		if (!image)
			return ErrCode::ERR_IMAGE_LOAD_FAIL;

		//store width and height
		m_width = image->header.width;
		m_height = image->header.height;

		//now that we have our image data, create opengl texture handle
		glGenTextures(1, &m_id);
		m_uniqueID = m_id; //store gl texture id as unique id

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//bind opengl texture handle
		glBindTexture(m_target, m_id);



		//retrieve internal format
		GLenum internalFormat = vixFIBmpToInternalFormat(image->bitmap);
		//retrieve format
		GLenum format = vixFIBmpToFormat(image->bitmap);
		glTexImage2D(m_target, 0, internalFormat, image->header.width, image->header.height, 0, format, GL_UNSIGNED_BYTE, image->data);
		glGenerateMipmap(m_target);
		glTexParameterf(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);




		//cleanup image allocation
		if (image)
			delete image;

		return ErrCode::ERR_SUCCESS;
	}

	ErrCode GLTexture::InitFromFIBMP(FREEIMAGE_BMP* bitmap)
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


		return ErrCode::ERR_SUCCESS;
	}

}
