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

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_tinyxml.h>
#include <vix_rectangle.h>
#include <vix_freeimage.h>
#include <vix_stlutil.h>
#include <vix_containers.h>
#include <atomic>
#include <thread>


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
	class VIX_API BMFont
	{
		typedef std::map<UChar, BMFontChar>    BMCharMap;

	public:
		/*Constructor for BMFont*/
		BMFont(File* file);

		/*Destructor for BMFont*/
		~BMFont();


		/*Getter functions*/
		const BMFontFile FontFile() const;

		Texture* const PageTexture(size_t index) const;

		/*Functions*/
		Rectangle  Bounds(const UString& text);

		void Load();


		friend UOStream& operator << (UOStream& o, const BMFont& font);

		/*Find font character in char map*/
		bool FindChar(UChar c, BMFontChar& fc);

		/*Initialize Textures*/
		void InitTextures();


		bool IsInitialized();

		bool IsLoaded();

	private:

		/*Static load function for loading BMFont file*/
		BMFontFile LoadFile(File* file);

		/*Adds a bitmap to the font page bitmap collection*/
		void LoadPageBitmap(const UString filePath);

		/*Adds a texture to the font page tex collection*/
		void AddPageTexture(Texture* texture);

		/*Static parse functions for reading the XML Font file*/
		static void ReadFontInfo(XMLDOC& doc, BMFontFile& file);
		static void ReadFontCommon(XMLDOC& doc, BMFontFile& file);
		static void ReadFontPages(XMLDOC& doc, BMFontFile& file);
		static void ReadFontChars(XMLDOC& doc, BMFontFile& file);

	private:
		std::vector<FREEIMAGE_BMP*> m_bitmaps;
		std::vector<Texture*>		m_textures;
		BMCharMap					m_charMap;
		BMFontFile					m_fontFile;
		bool						m_initialized;
		std::atomic<bool>           m_loaded;
	};


	inline UOStream& operator << (UOStream& o, const BMFont& font)
	{
		/*Will fail if UNICODE and outputting to console window without UTF-8 locale set*/
		o << font.FontFile().ToString();

		return o;
	}
}

#endif
