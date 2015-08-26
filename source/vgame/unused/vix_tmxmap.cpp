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

#include <vix_tmxmap.h>
#include <vix_debugutil.h>

namespace Vixen {


	/***********************TMXLAYER*********************/

	TMXLayer::TMXLayer(const UString& name,
							size_t	  width,
							size_t	  height,
							float	  opacity,
							bool	  visible)
	{
		m_name = name;
		m_width = width;
		m_height = height;
		m_opacity = opacity;
		m_visible = visible;
	}

	TMXLayer::~TMXLayer(void)
	{
		if(m_tiles)
			delete[] m_tiles;
	}

	void TMXLayer::SetTile(int row, int col, const TMXTile& tile)
	{
		m_tiles[m_width * row + col] = tile;
	}

	void TMXLayer::SetTileID(int row, int col, int val)
	{
		m_tiles[m_width * row + col].globalID = val;
	}

	const TMXTile& TMXLayer::GetTile(int row, int col)
	{
		return m_tiles[m_width * row + col];
	}

	int TMXLayer::GetTileID(int row, int col)
	{
		return m_tiles[m_width * row + col].globalID;
	}

	/***********************TMXMAP************************/

	TMXMap::TMXMap(void)
	{

	}

	void TMXMap::FromFile(const UString& file, TMXMap& map)
	{
		using namespace tinyxml2;

		/*Try Parse file*/
		XMLDOC document;

		/*TinyXML now supports paths containing UTF-8 encoded characters due to
		  change I've made in the source. */
		XMLError err = document.LoadFile(file.c_str());
		UString errorString;
		if (XMLErrCheck(err, errorString)) {
			DebugPrintF(VTEXT("XMLDocument Load Failed: %s\n"),
				        errorString.c_str());
			return;
		}

		ReadMapInfo(document, map);
		ReadTilesetInfo(document, map);
	}

	void TMXMap::ReadMapInfo(XMLDOC& document, TMXMap& map)
	{
		using namespace tinyxml2;

		XMLElement* mapinfo = document.FirstChildElement("map");
		map.m_info.version = mapinfo->DoubleAttribute("version");
		const char* orientation = mapinfo->Attribute("orientation");

	}

	void TMXMap::ReadTilesetInfo(XMLDOC& document, TMXMap& map)
	{

	}
}
