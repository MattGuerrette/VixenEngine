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

#ifndef VIX_TEXTURE_H
#define VIX_TEXTURE_H

#include <vix_platform.h>
#include <vix_freeimage.h>
#include <vix_file.h>
#include <vix_asset.h>

namespace Vixen {

	class VIX_API Texture : public Asset
	{
	public:
		Texture();

        virtual ~Texture() { }

        virtual bool VInitFromBMP(FREEIMAGE_BMP* bmp) = 0;

        virtual size_t VGetWidth() const = 0;
        virtual size_t VGetHeight() const = 0;
	};
}

#endif
