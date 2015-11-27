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
