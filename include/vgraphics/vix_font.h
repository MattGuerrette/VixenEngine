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

#ifndef VIX_FONT_H
#define VIX_FONT_H

#include <vix_platform.h>
#include <vix_file.h>
#include <vix_texture.h>
#include <vix_containers.h>
#include <vix_rectangle.h>
#include <vix_asset.h>

namespace Vixen {

    struct VIX_API FontChar
    {
        int id;
        int x;
        int y;
        int width;
        int height;
        int xOffset;
        int yOffset;
        int xAdvance;
        int page;
        int channel;
    };

    class VIX_API Font : public Asset
    {
    public:
        typedef std::map<UChar, FontChar> CharMap;

		Font();

        virtual ~Font() { };

        virtual Texture* VPageTexture(size_t index) = 0;
        virtual bool      VFindChar(UChar c, FontChar& fontChar) = 0;
        virtual float     VLineHeight() = 0;

		virtual Rect       VBounds(UString text) = 0;

    };

}

#endif
