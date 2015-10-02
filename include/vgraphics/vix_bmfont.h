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