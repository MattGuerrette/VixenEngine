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

#include <vix_bmfont.h>
#include <vix_tinyxml.h>
#include <vix_debugutil.h>
#include <vix_resourcemanager.h>
#include <vix_rectangle.h>

namespace Vixen {

    BMFont::BMFont()
    {

    }

    BMFont::~BMFont()
    {
        STLVEC_DELETE(m_textures);
    }

    bool BMFont::VInitFromFile(File* file)
    {
        using namespace tinyxml2;

        XMLDOC document;
        XMLError err = document.LoadFile(file->Handle());
        UString errString;
        if (XMLErrCheck(err, errString))
        {
            DebugPrintF(VTEXT("BMFont File failed to load\n"));
            return false;
        }

        BMFont::ReadFontInfo(document, m_fontFile);
        BMFont::ReadFontCommon(document, m_fontFile);
        BMFont::ReadFontPages(document, m_fontFile);
        BMFont::ReadFontChars(document, m_fontFile);

        for (FontChar& c : m_fontFile.chars)
        {
            UChar _c = (UChar)c.id;
            m_charMap[_c] = c;
        }

        for (auto& page : m_fontFile.pages) {
            UString texturePath = page.file;
            ITexture* texture = ResourceManager::OpenTexture(texturePath);
            if (texture)
                m_textures.push_back(texture);
        }

        return true;
    }

    ITexture* BMFont::VPageTexture(size_t index)
    {
        if (index > m_textures.size())
            return NULL;

        return m_textures[index];
    }

    bool BMFont::VFindChar(UChar c, FontChar& fontChar)
    {
        IFont::CharMap::iterator it = m_charMap.find(c);
        if (it != m_charMap.end())
        {
            fontChar = it->second;
            return true;
        }
        else
            return false;
    }

    float BMFont::VLineHeight()
    {
        return m_fontFile.common.lineHeight;
    }


	Rect BMFont::VBounds(UString text)
	{
		Rect bounds;
		int dx = 0;
		int lineH = m_fontFile.common.lineHeight;
		int dy = lineH;
		/*Iterate over characters in text*/
		for (const UChar& c : text)
		{
			if (c == '\n') {
				dx = 0;
				dy += lineH;
			}

			//Find the font character and advance the
			//pixel units based on the xAdvance value
			FontChar fc;
			if (VFindChar(c, fc)) {
				dx += fc.xAdvance;
			}
		}

		bounds.x = 0;
		bounds.y = 0;
		bounds.w = dx;
		bounds.h = dy;

		return bounds;
	}


    void BMFont::ReadFontInfo(XMLDOC& doc, BMFontFile& file)
    {
        using namespace tinyxml2;
        XMLElement* fontElement = doc.FirstChildElement("font");
        XMLElement* infoElement = fontElement->FirstChildElement("info");

        /*Populate font info struct of file with parsed info*/
        BMFontInfo& info = file.info;

        const char* _face = infoElement->Attribute("face");
        const char* _charset = infoElement->Attribute("charset");
        const char* _padding = infoElement->Attribute("padding");
        const char* _spacing = infoElement->Attribute("spacing");
        UString spacing;
#ifdef UNICODE
        UConverter cv;
        info.face = cv.from_bytes(_face);
        info.charset = cv.from_bytes(_charset);
        info.padding = cv.from_bytes(_padding);
        spacing = cv.from_bytes(_spacing);
#else
        info.face = _face;
        info.charset = _charset;
        info.padding = _padding;
        spacing = _spacing;
#endif
        info.size = infoElement->IntAttribute("size");
        info.bold = infoElement->IntAttribute("bold");
        info.italic = infoElement->IntAttribute("italic");
        info.unicode = infoElement->IntAttribute("unicode");
        info.stretchH = infoElement->IntAttribute("stretchH");
        info.smooth = infoElement->IntAttribute("smooth");
        info.antiAliasing = infoElement->IntAttribute("aa");
        /*Need to parse the padding values*/
        std::vector<int> paddingValues = parse<int>(info.padding, ',');
        info.padX = paddingValues[0];
        info.padY = paddingValues[1];
        info.padW = paddingValues[2];
        info.padH = paddingValues[3];
        /*Need to parse the spacing values*/
        std::vector<int> spacingValues = parse<int>(spacing, L',');
        info.spacingX = spacingValues[0];
        info.spacingY = spacingValues[1];
        info.outline = infoElement->IntAttribute("outline");
    }

    void BMFont::ReadFontCommon(XMLDOC& doc, BMFontFile& file)
    {
        using namespace tinyxml2;
        XMLElement* fontElement = doc.FirstChildElement("font");
        XMLElement* commonElement = fontElement->FirstChildElement("common");

        /*Populate font common struct of file*/
        BMFontCommon& common = file.common;
        common.lineHeight = commonElement->IntAttribute("lineHeight");
        common.base = commonElement->IntAttribute("base");
        common.scaleW = commonElement->IntAttribute("scaleW");
        common.scaleH = commonElement->IntAttribute("scaleH");
        common.pages = commonElement->IntAttribute("pages");
        common.packed = commonElement->IntAttribute("packed");
        common.alphaChannel = commonElement->IntAttribute("alphaChnl");
        common.redChannel = commonElement->IntAttribute("redChnl");
        common.greenChannel = commonElement->IntAttribute("greenChnl");
        common.blueChannel = commonElement->IntAttribute("blueChnl");
    }

    void BMFont::ReadFontChars(XMLDOC& doc, BMFontFile& file)
    {
        using namespace tinyxml2;
        XMLElement* fontElement = doc.FirstChildElement("font");
        XMLElement* charsElement = fontElement->FirstChildElement("chars");
        int count = charsElement->IntAttribute("count");

        /*Populate font file chars collection*/
        std::vector<FontChar>& chars = file.chars;
        XMLElement* charElement = charsElement->FirstChildElement("char");
        for (int i = 0; i < count; i++)
        {

            FontChar c;
            c.id = charElement->IntAttribute("id");
            c.x = charElement->IntAttribute("x");
            c.y = charElement->IntAttribute("y");
            c.width = charElement->IntAttribute("width");
            c.height = charElement->IntAttribute("height");
            c.xOffset = charElement->IntAttribute("xoffset");
            c.yOffset = charElement->IntAttribute("yoffset");
            c.xAdvance = charElement->IntAttribute("xadvance");
            c.page = charElement->IntAttribute("page");
            c.channel = charElement->IntAttribute("chnl");
            chars.push_back(c);

            /*move to next char element*/
            charElement = charElement->NextSiblingElement("char");
        }
    }

    void BMFont::ReadFontPages(XMLDOC& doc, BMFontFile& file)
    {
        using namespace tinyxml2;
        XMLElement* fontElement = doc.FirstChildElement("font");
        XMLElement* pagesElement = fontElement->FirstChildElement("pages");

        /*Populate font file pages collection*/
        std::vector<BMFontPage>& pages = file.pages;
        XMLElement* pageElement = pagesElement->FirstChildElement("page");
        while (pageElement)
        {
            BMFontPage p;
            p.id = pageElement->IntAttribute("id");
            const char* _file = pageElement->Attribute("file");

#ifdef UNICODE
            UConverter cv;
            p.file = cv.from_bytes(_file);
#else
            p.file = _file;
#endif
            pages.push_back(p);

            /*Try and move to next page element*/
            pageElement = pageElement->NextSiblingElement("page");
        }
    }
}
