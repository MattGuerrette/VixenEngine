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

#include <vix_contentmanager.h>
#include <vix_stlutil.h>

namespace Vixen {


	ContentManager::ContentManager()
	{

	}

	ContentManager::~ContentManager()
	{
        STLMAP_DELETE(m_fonts);
	}

  BMFont* ContentManager::LoadFont(const UString& path)
  {
    	if (path.empty()) {
	  DebugPrintF(VTEXT("Error Loading [BMFont]"));
			return NULL;
		}

		UString _path = os_path(FONT_FOLDER_PATH + path);
		UString _texPath = os_path(FONT_FOLDER_PATH + TEX_FOLDER_PATH);

		ContentMap::iterator it = m_fonts.find(_path);
		if (it != m_fonts.end()) {
			return (BMFont*)it->second;
		}
		else {

			/*create new font*/
			BMFont* font = new BMFont(_path);
			/*load textures for font*/
			for (auto& page : font->FontFile().pages) {
				Texture* tex = LoadTexture(_texPath + page.file);
				if (tex)
					font->AddPageTexture(tex);
			}
			m_fonts[_path] = (IContent*)font;
			return font;
		}

		return NULL;
  }

  Texture* ContentManager::LoadTexture(const UString& path)
  {
    	if (path.empty()) {
	  DebugPrintF(VTEXT("Error Loading [Texture]"));
			return NULL;
		}

		UString _path = os_path(TEX_FOLDER_PATH + path);

		ContentMap::iterator it = m_textures.find(_path);
		if (it != m_textures.end()) {
			return (Texture*)it->second;
		}
		else {
			/*create new texture*/
			Texture* texture = new GLTexture(_path);
			m_textures[_path] = (IContent*)texture;
			return texture;
		}

		return NULL;
  }

	ErrCode ContentManager::VStartUp()
	{
		DebugPrintF(VTEXT("ContentManager starting up..."));

		return ErrCode::ERR_SUCCESS;
	}

	ErrCode ContentManager::VShutDown()
	{
		DebugPrintF(VTEXT("ContentManager shutting down..."));

		return ErrCode::ERR_SUCCESS;
	}

	void ContentManager::DumpTextures()
	{
		for (auto& tex : m_textures)
		{
			Texture* _tex = (Texture*)tex.second;
			DebugPrintF(VTEXT("Texture [%s]\n"), _tex->name().c_str());
		}
	}
}
