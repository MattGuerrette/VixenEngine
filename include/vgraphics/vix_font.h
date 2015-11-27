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
