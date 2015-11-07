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
