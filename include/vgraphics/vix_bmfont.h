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


#ifndef VIX_BMFONT_H
#define VIX_BMFONT_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_tinyxml.h>
#include <vix_rectangle.h>
#include <vix_content.h>
#include <vector>
#include <map>


namespace Vixen {


	struct VIX_API BMFontChar
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

		friend UOStream& operator << (UOStream& o, const BMFontChar& c);
	};


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

		friend VIX_API UOStream& operator << (UOStream& o, const BMFontInfo& i);
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

		friend VIX_API UOStream& operator << (UOStream& o, const BMFontCommon& c);
	};



	struct VIX_API BMFontPage
	{
		int         id;
		UString     file;

		friend VIX_API UOStream& operator << (UOStream& o, const BMFontPage& p);
	};


	struct VIX_API BMFontKerning
	{
		int  first;
		int  second;
		int  amount;

		friend VIX_API UOStream& operator << (UOStream& o, const BMFontKerning& k);
	};



	struct VIX_API BMFontFile
	{
		UString                     file;
		BMFontInfo                  info;
		BMFontCommon                common;
		std::vector<BMFontPage>     pages;
		std::vector<BMFontChar>     chars;
		std::vector<BMFontKerning>  kernings;

		UString ToString() const;
	};


	class Texture;

	/**
	* BMFont class
	* Desc:
	* Font class used to descibe fonts created by the BMFont tool
	* created by AngelCode and avaliable at: http://www.angelcode.com/products/bmfont/
	*/
	class VIX_API BMFont : IContent
	{
		typedef std::map<UChar, BMFontChar>    BMCharMap;

	public:
		/*Constructor for BMFont*/
		BMFont(const UString& filePath);

		/*Adds a texture to the font page tex collection*/
		void AddPageTexture(Texture* texture);

		/*Getter functions*/
		const BMFontFile FontFile() const;

		Texture* const PageTexture(size_t index) const;

		/*Functions*/
		Rectangle  Bounds(const UString& text);

		/*Static parse functions for reading the XML Font file*/
		static void ReadFontInfo(XMLDOC& doc, BMFontFile& file);
		static void ReadFontCommon(XMLDOC& doc, BMFontFile& file);
		static void ReadFontPages(XMLDOC& doc, BMFontFile& file);
		static void ReadFontChars(XMLDOC& doc, BMFontFile& file);

		/*Static load function for loading BMFont file*/
		static BMFontFile LoadFile(const UString& filePath);


		friend UOStream& operator << (UOStream& o, const BMFont& font);

		/*Find font character in char map*/
		bool FindChar(UChar c, BMFontChar& fc);

		/*Initialize Textures*/
		void InitTextures();

	private:
		std::vector<FREEIMAGE_BMP*> m_bitmaps;
		std::vector<Texture*>		m_textures;
		BMCharMap					m_charMap;
		BMFontFile					m_fontFile;
		bool                        m_initialized;
	};


	inline UOStream& operator << (UOStream& o, const BMFont& font)
	{
		/*Will fail if UNICODE and outputting to console window without UTF-8 locale set*/
		o << font.FontFile().ToString();

		return o;
	}
}

#endif
