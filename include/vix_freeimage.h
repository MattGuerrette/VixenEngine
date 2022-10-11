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

#ifndef VIX_FREEIMAGE_H
#define VIX_FREEIMAGE_H

#include "vix_platform.h"
#include "vix_stringutil.h"
#include "vix_file.h"
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
