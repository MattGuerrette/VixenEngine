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

#ifndef VIX_BMFONT_H
#define VIX_BMFONT_H

#include <vix_platform.h>
#include <vix_font.h>
#include <vix_tinyxml.h>

namespace Vixen {

    struct VIX_API BMFontInfo
    {
        UString    face;
        int            size;
        int            bold;
        int            italic;
        UString    charset;
        int            unicode;
        int            stretchH;
        int            smooth;
        int            antiAliasing;
        UString    padding;
        int            padX;
        int            padY;
        int            padW;
        int            padH;
        int            spacingX;
        int            spacingY;
        int            outline;
    };


    struct VIX_API BMFontCommon
    {
        int lineHeight;
        int base;
        int scaleW;
        int scaleH;
        int pages;
        int packed;
        int alphaChannel;
        int redChannel;
        int greenChannel;
        int blueChannel;
    };



    struct VIX_API BMFontPage
    {
        int         id;
        UString     file;
    };


    struct VIX_API BMFontKerning
    {
        int  first;
        int  second;
        int  amount;
    };

    struct VIX_API BMFontFile
    {
        UString                     file;
        BMFontInfo                  info;
        BMFontCommon                common;
        std::vector<BMFontPage>     pages;
        std::vector<FontChar>       chars;
        std::vector<BMFontKerning>  kernings;
    };

    class VIX_API BMFont : public IFont
    {
    public:
        BMFont();

        ~BMFont();

        bool        VInitFromFile(File* file);
        ITexture*   VPageTexture(size_t index);
        bool        VFindChar(UChar c, FontChar& fontChar);

        float       VLineHeight();

<<<<<<< HEAD
=======
		Rect		VBounds(UString text);
      
>>>>>>> 5d61730afc80281f2da012a8e50084e490f8a879

    private:
        IFont::CharMap          m_charMap;
        BMFontFile              m_fontFile;
        std::vector<ITexture*>  m_textures;

    private:
        /*Static parse functions for reading the XML Font file*/
        static void ReadFontInfo(XMLDOC& doc, BMFontFile& file);
        static void ReadFontCommon(XMLDOC& doc, BMFontFile& file);
        static void ReadFontPages(XMLDOC& doc, BMFontFile& file);
        static void ReadFontChars(XMLDOC& doc, BMFontFile& file);
    };

}

#endif
