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

#ifndef VIX_FREEIMAGE_H
#define VIX_FREEIMAGE_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_file.h>
#include <FreeImage.h>

namespace Vixen {

	struct FREEIMAGE_HEADER
	{
		size_t width;
		size_t height;
		size_t bitdepth;
	};

	struct FREEIMAGE_BMP
	{
		UString           name;
		UString           path;
		FIBITMAP*         bitmap;
		FREE_IMAGE_FORMAT format;
		BYTE*			  data;
		FREEIMAGE_HEADER  header;

		~FREEIMAGE_BMP()
		{
			if (bitmap)
				FreeImage_Unload(bitmap);
		}
	};

	VIX_API FREE_IMAGE_FORMAT	FREEIMAGE_FormatFromExtension(const UString& ext);
	VIX_API FREEIMAGE_BMP*		FREEIMAGE_LoadImage(const UString& filePath);
	VIX_API FREEIMAGE_BMP*		FREEIMAGE_LoadImage(const UString& filePath, BYTE* raw_data, int len);
	VIX_API void                FREEIMAGE_LoadPNGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data);
	VIX_API void                FREEIMAGE_LoadJPGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data);
	VIX_API void                FREEIMAGE_LoadTGAHeader(FREEIMAGE_HEADER* header, BYTE* raw_data);
}

#endif
