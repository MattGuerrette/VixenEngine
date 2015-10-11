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
        size_t            bpp;

		~FREEIMAGE_BMP()
		{
			if (bitmap)
				FreeImage_Unload(bitmap);
		}
	};

	VIX_API FREE_IMAGE_FORMAT	FREEIMAGE_FormatFromExtension(const UString& ext);
	VIX_API FREEIMAGE_BMP*		FREEIMAGE_LoadImage(const UString& filePath);
	VIX_API FREEIMAGE_BMP*		FREEIMAGE_LoadImage(const UString& filePath, BYTE* raw_data, int len);
	VIX_API FREEIMAGE_BMP*		FREEIMAGE_LoadImage(File* file);
	VIX_API void                FREEIMAGE_LoadPNGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data);
	VIX_API void                FREEIMAGE_LoadJPGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data);
	VIX_API void                FREEIMAGE_LoadTGAHeader(FREEIMAGE_HEADER* header, BYTE* raw_data);
}

#endif
