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

#ifndef VIX_BMFONT_H
#define VIX_BMFONT_H

#include "vix_platform.h"
#include "vix_font.h"
#include "vix_tinyxml.h"

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

    class VIX_API BMFont : public Font
    {
    public:
        BMFont();

        ~BMFont();

        bool        VInitFromFile(File* file);
        Texture*    VPageTexture(size_t index);
        bool        VFindChar(UChar c, FontChar& fontChar);

        float       VLineHeight();

		Rect		VBounds(UString text);


    private:
        Font::CharMap          m_charMap;
        BMFontFile              m_fontFile;
        std::vector<Texture*>  m_textures;

    private:
        /*Static parse functions for reading the XML Font file*/
        static void ReadFontInfo(XMLDOC& doc, BMFontFile& file);
        static void ReadFontCommon(XMLDOC& doc, BMFontFile& file);
        static void ReadFontPages(XMLDOC& doc, BMFontFile& file);
        static void ReadFontChars(XMLDOC& doc, BMFontFile& file);
    };

}

#endif
