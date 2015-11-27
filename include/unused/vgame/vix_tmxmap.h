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

#ifndef VIX_TMXMAP_H
#define VIX_TMXMAP_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_tinyxml.h>

namespace Vixen {

	enum TMXImgFormat
	{
		TMX_PNG,
		TMX_GIF,
		TMX_JPG,
		TMX_BMP
	};

	enum TMXOrientation
	{
		ORTHOGONAL,
		ISOMETRIC,
		STAGGERED
	};

	enum TMXRenderOrder
	{
		RIGHTDOWN,
		RIGHTUP,
		LEFTDOWN,
		LEFTUP
	};

	struct TMXMapInfo
	{
		double			version;	  //TMX format version (usually 1.0)
		TMXOrientation	orientation;  //Map orientation. Orthogonal, Isometric, Staggered
		TMXRenderOrder  renderOrder;
		size_t          width;		  //Width of map in TILES
		size_t          height;		  //Height of map in TILES
		size_t          tileWidth;    //Pixel width of tile
		size_t          tileHeight;   //Pixel height of tile
	};

	struct TMXImageInfo
	{
		TMXImgFormat	format;		//EXT. FOR EMBEDDED IMAGES
		UString			source;		//Path reference to tileset image file
		size_t			width;		//Width of image in pixels  (optional)
		size_t			height;		//Height of image in pixels (optional)
	};

	struct TMXTilesetInfo
	{
		int		globalID;	//first global tile ID (maps to FIRST tile)
		UString name;		//name
		size_t  width;		//maximum width of tiles
		size_t  height;		//maximum height of tiles
		size_t  spacing;	//spacing in pixels between tiles
		size_t  margin;		//margin around tiles
	};

	struct TMXTile
	{
		int    globalID;	//local tile ID within tileset
	};


	class VIX_API TMXLayer
	{
	public:
		TMXLayer(const UString& name,
					   size_t	width,
					   size_t	height,
					   float	opacity,
					   bool		visible);

		~TMXLayer(void);

		void			SetTile(int row, int col, const TMXTile& tile);
		void			SetTileID(int row, int col, int val);
		const TMXTile&	GetTile(int row, int col);
		int				GetTileID(int row, int col);

	private:
		UString		m_name;		//layer name
		size_t		m_width;	//width in TILES
		size_t		m_height;	//height in TILES
		float		m_opacity;	//opacity of layer (0 - 1)
		bool		m_visible;	//layer visibility (true - false)
		TMXTile*	m_tiles;    //tile collection
	};

	class VIX_API TMXMap
	{
	public:
		TMXMap(void);


		static void FromFile(const UString& file, TMXMap& map);
	private:
		TMXMapInfo m_info;
		TMXLayer*  m_layers;

	private:
		static void				ReadMapInfo(XMLDOC& document, TMXMap& map);
		static void				ReadTilesetInfo(XMLDOC& document, TMXMap& map);
	};

}

#endif
