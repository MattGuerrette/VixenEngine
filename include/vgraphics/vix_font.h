/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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
