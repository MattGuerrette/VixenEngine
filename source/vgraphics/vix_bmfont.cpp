/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

#include <vix_bmfont.h>
#include <vix_debugutil.h>
#include <vix_errglobals.h>
#include <vix_algorithms.h>
#include <vix_texture.h>
#include <vix_gltexture.h>
#include <vix_pathmanager.h>
#include <vix_filemanager.h>
#ifndef VIX_SYS_LINUX
#include <codecvt>
#endif



namespace Vixen {

	VIX_API UOStream& operator << (UOStream& o, const BMFontInfo& i)
	{
		o << "[BMFontInfo]\n"
			<< "\tFace=" << i.face << "\n"
			<< "\tSize=" << i.size << "\n"
			<< "\tBold=" << i.bold << "\n"
			<< "\tItalic=" << i.italic << "\n"
			<< "\tCharSet=" << i.charset << "\n"
			<< "\tUnicode=" << i.unicode << "\n"
			<< "\tStretchH=" << i.stretchH << "\n"
			<< "\tSmooth=" << i.smooth << "\n"
			<< "\tAA=" << i.antiAliasing << "\n"
			<< "\tPadding=" << i.padding << "\n"
			<< "\tPadX=" << i.padX << "\n"
			<< "\tPadY=" << i.padY << "\n"
			<< "\tPadW=" << i.padW << "\n"
			<< "\tPadH=" << i.padH << "\n"
			<< "\tSpacingX=" << i.spacingX << "\n"
			<< "\tSpacingY=" << i.spacingY << "\n"
			<< "\tOutline=" << i.outline << "\n";

		return o;
	}

	VIX_API UOStream& operator << (UOStream& o, const BMFontCommon& c)
	{
		o << "[BMFontCommon]\n"
		<< "\tLineHeight=" << c.lineHeight << "\n"
		<< "\tBase=" << c.base << "\n"
		<< "\tScaleW=" << c.scaleW << "\n"
		<< "\tScaleH=" << c.scaleH << "\n"
		<< "\tPages=" << c.pages << "\n"
		<< "\tPacked=" << c.packed << "\n"
		<< "\tAlpha=" << c.alphaChannel << "\n"
		<< "\tRed=" << c.redChannel << "\n"
		<< "\tGreen=" << c.greenChannel << "\n"
		<< "\tBlue=" << c.blueChannel << "\n";

		return o;
	}


	VIX_API UOStream& operator << (UOStream& o, const BMFontPage& p)
	{
		o << "[BMFontPage]\n"
		<< "\tID=" << p.id << "\n"
		<< "\tFile=" << p.file << "\n";

		return o;
	}

	VIX_API UOStream& operator << (UOStream& o, const BMFontKerning& k)
	{
		o << "[BMFontKerning]\n"
			<< "\tFirst=" << k.first << "\n"
			<< "\tSecond=" << k.second << "\n"
			<< "\tAmount=" << k.amount << "\n";

		return o;
	}

	UString BMFontFile::ToString() const
	{
		USStream ss;
		ss << "---BMFontFile---" << "\n" << "\n"
			<< "File: " << file << "\n"
			<< info << "\n" << common;
		for (const BMFontPage& page : pages)
		{
			ss << page << "\n";
		}
		return ss.str();
	}

	BMFont::BMFont(File* file)
	{
		m_initialized = false;
		m_loaded = false;

		m_fontFile = LoadFile(file);

		/*Create character map*/
		for (BMFontChar& fontChar : m_fontFile.chars)
		{
			UChar c = (UChar)fontChar.id;
			m_charMap[c] = fontChar;
		}
	}

	BMFont::~BMFont()
	{
		STLVEC_DELETE(m_bitmaps);
		STLVEC_DELETE(m_textures);
	}

	void BMFont::Load()
	{
		//Start thread and detach to load bitmap images
		//asynchronously.
		std::thread t([&](BMFont* font, std::atomic<bool>* finished) {

			/*Need to load all page bitmaps*/
			UString assetPath = PathManager::instance().AssetPath();

			for (auto& page : font->m_fontFile.pages) {
				UString texPath = assetPath + VTEXT("Fonts/Textures/") + page.file;
				FileManager::instance().OpenFile(texPath);
				File* bitmapFile = FileManager::instance().AccessFile(texPath);
				if(bitmapFile) {
					FREEIMAGE_BMP* bmp = FREEIMAGE_LoadImage(bitmapFile);
					if(bmp)
						font->m_bitmaps.push_back(bmp);
				}
			}

			*finished = true;
		}, this, &m_loaded);
		t.detach(); //run the async thread
	}

	void BMFont::AddPageTexture(Texture* texture)
	{
		if (!texture) {
			DebugPrintF(VTEXT("Cannot add NULL texture"));
			return;
		}

		/*Check if texture doesn't already exist in collection*/
		std::vector<Texture*>::iterator it;
		it = std::find(m_textures.begin(), m_textures.end(), texture);
		if (it == m_textures.end()) {
			/*we can safely add the texture to our collection*/
			m_textures.push_back(texture);
		}
		else {
			DebugPrintF(VTEXT("Texture %s already exists in BMFont collection"),
				        texture->name().c_str());
			return;
		}
	}

	void BMFont::LoadPageBitmap(const UString filePath)
	{
		/*if (!bitmap) {
			DebugPrintF(VTEXT("Cannot add NULL bitmap"));
			return;
		}*/
		FREEIMAGE_BMP* bmp = Vixen::FREEIMAGE_LoadImage(filePath);
		if(bmp)
			m_bitmaps.push_back(bmp);
	}

	void BMFont::InitTextures()
	{
		if (!m_initialized) {
			for (auto& bitmap : m_bitmaps) {
				GLTexture* tex = new GLTexture(bitmap);
				m_textures.push_back(tex);
			}
			STLVEC_DELETE(m_bitmaps);
			m_initialized = true;
		}
	}

	bool BMFont::IsInitialized()
	{
		return m_initialized;
	}

	bool BMFont::IsLoaded()
	{
		return m_loaded;
	}

	const BMFontFile BMFont::FontFile() const
	{
		return m_fontFile;
	}

	Texture* const BMFont::PageTexture(size_t index) const
	{
		if (index > m_textures.size())
			return nullptr;

		return m_textures[index];
	}

	/*Returns the pixel unit bounds of a string of text*/
	Rectangle BMFont::Bounds(const UString& text)
	{
		Rectangle bounds;
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
			BMFontChar fc;
			if (FindChar(c, fc)) {
				dx += fc.xAdvance;
			}
		}

		bounds.x = 0;
		bounds.y = 0;
		bounds.w = dx;
		bounds.h = dy;

		return bounds;
	}

	bool BMFont::FindChar(UChar c, BMFontChar& fc)
	{
		BMCharMap::iterator it = m_charMap.find(c);
		if (it != m_charMap.end())
		{
			fc = it->second;
			return true;
		}
		else
			return false;
	}

	BMFontFile BMFont::LoadFile(File* file)
	{
		using namespace tinyxml2;

		BMFontFile fontFile;

		/*set file attribute of font file*/
		fontFile.file = file->FilePath();

		/*Try Parse file*/
		XMLDOC document;
		/*TinyXML now supports paths containing UTF-8 encoded characters due to
		  change I've made in the source. */
		XMLError err = document.LoadFile(file->Handle());
		UString errorString;
		if (XMLErrCheck(err, errorString)) {
			DebugPrintF(VTEXT("XMLDocument [%s] Load Failed\n"),
				        file->FilePath().c_str());
			return fontFile;
		}

		/*Read file contents into bmfont file struct*/
		BMFont::ReadFontInfo(document, fontFile);
		BMFont::ReadFontCommon(document, fontFile);
		BMFont::ReadFontPages(document, fontFile);
		BMFont::ReadFontChars(document, fontFile);

		return fontFile;
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
		std::vector<BMFontChar>& chars = file.chars;
		XMLElement* charElement = charsElement->FirstChildElement("char");
		for (int i = 0; i < count; i++)
		{

			BMFontChar c;
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
