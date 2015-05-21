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

#include <vix_freeimage.h>

namespace Vixen {

	FREE_IMAGE_FORMAT
	FREEIMAGE_FormatFromExtension(const UString& ext)
	{
		if (ext == VTEXT("png"))
			return FIF_PNG;
		if (ext == VTEXT("jpg"))
			return FIF_JPEG;
		if (ext == VTEXT("bmp"))
			return FIF_BMP;
		if (ext == VTEXT("tga"))
			return FIF_TARGA;

		return FIF_UNKNOWN;
	}

	void
	FREEIMAGE_LoadPNGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data)
	{
		if (!header || !raw_data)
			return;

		header->width = (raw_data[16] << 24) + (raw_data[17] << 16) + (raw_data[18] << 8) + (raw_data[19] << 0);
		header->height = (raw_data[20] << 24) + (raw_data[21] << 16) + (raw_data[22] << 8) + (raw_data[23] << 0);
		header->bitdepth = (raw_data[24]);
	}

	void
	FREEIMAGE_LoadJPGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data)
	{
		if (!header || !raw_data)
			return;

		header->width = (raw_data[12] << 8) + (raw_data[13] << 0);
		header->height = (raw_data[14] << 8) + (raw_data[15] << 0);
	}

	void
	FREEIMAGE_LoadTGAHeader(FREEIMAGE_HEADER* header, BYTE* raw_data)
	{
		header->width = (raw_data[12] << 8) + (raw_data[13] << 0);
		header->height = (raw_data[14] << 8) + (raw_data[15] << 0);
	}

	FREEIMAGE_BMP*
	FREEIMAGE_LoadImage(const UString& filePath)
	{
		FREEIMAGE_BMP* vix_bmp = new FREEIMAGE_BMP;
		vix_bmp->path = filePath;
		vix_bmp->name = getFileName(filePath);
		vix_bmp->format = FREEIMAGE_FormatFromExtension(getFileExtension(filePath, false));
		vix_bmp->data = NULL;
		vix_bmp->bitmap = NULL;

		/*Here we must */

		//Check file signature and deduce format
#ifdef UNICODE
		vix_bmp->format = FreeImage_GetFileTypeU(filePath.c_str());
#else
		vix_bmp->format = FreeImage_GetFileType(filePath.c_str());
#endif
		if (vix_bmp->format == FIF_UNKNOWN) {
#ifdef UNICODE
			vix_bmp->format = FreeImage_GetFIFFromFilenameU(filePath.c_str());
#else
			vix_bmp->format = FreeImage_GetFIFFromFilename(filePath.c_str());
#endif
		}

		//if still unknown, return NULL;
		if (vix_bmp->format == FIF_UNKNOWN)
			return NULL;

		//Check if FreeImage has reading capabilities
		if (FreeImage_FIFSupportsReading(vix_bmp->format)) {
#ifdef UNICODE
			//read image into struct pointer
			vix_bmp->bitmap = FreeImage_LoadU(vix_bmp->format, filePath.c_str());
#else
			vix_bmp->bitmap = FreeImage_Load(vix_bmp->format, filePath.c_str());
#endif

		}

		//If image failed to load, return NULL
		if (!vix_bmp->bitmap)
			return NULL;

		FreeImage_FlipVertical(vix_bmp->bitmap);

		//Retrieve image data
		vix_bmp->data = FreeImage_GetBits(vix_bmp->bitmap);
		//Retrieve image width
		vix_bmp->header.width = FreeImage_GetWidth(vix_bmp->bitmap);
		//Retrieve image height
		vix_bmp->header.height = FreeImage_GetHeight(vix_bmp->bitmap);
		if (vix_bmp->data == 0 || vix_bmp->header.width == 0 || vix_bmp->header.height == 0)
			return NULL;

		//return bitmap
		return vix_bmp;
	}


	FREEIMAGE_BMP*
	FREEIMAGE_LoadImage(const UString& filePath, BYTE* raw_data, int len)
	{
		if (!raw_data)
			return NULL;

		FREEIMAGE_BMP* vix_bmp = new FREEIMAGE_BMP;
		vix_bmp->path = filePath;
		vix_bmp->name = getFileName(filePath);
		vix_bmp->format = FREEIMAGE_FormatFromExtension(getFileExtension(filePath, false));
		vix_bmp->data = NULL;
		vix_bmp->bitmap = NULL;
		switch (vix_bmp->format)
		{
		case FIF_PNG:
			FREEIMAGE_LoadPNGHeader(&vix_bmp->header, raw_data);
			break;
		case FIF_TARGA:
			FREEIMAGE_LoadTGAHeader(&vix_bmp->header, vix_bmp->data);
			break;

		case FIF_JPEG:
			FREEIMAGE_LoadJPGHeader(&vix_bmp->header, vix_bmp->data);
			break;
		}


		//Check if FreeImage has reading capabilities
		if (FreeImage_FIFSupportsReading(vix_bmp->format)) {

			int pitch = ((vix_bmp->header.bitdepth * vix_bmp->header.width + 31) / 32) * 4;
			vix_bmp->bitmap = FreeImage_ConvertFromRawBits(raw_data,
				                                           vix_bmp->header.width,
				                                           vix_bmp->header.height,
														   pitch,
														   vix_bmp->header.bitdepth * 4, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		}

		//If image failed to load, return NULL
		if (!vix_bmp->bitmap)
			return NULL;

		FreeImage_FlipVertical(vix_bmp->bitmap);

		//return bitmap
		return vix_bmp;
	}


}
