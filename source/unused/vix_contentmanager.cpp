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
