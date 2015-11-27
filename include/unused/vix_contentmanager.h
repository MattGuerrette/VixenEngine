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

#ifndef VIX_CONTENTMANAGER_H
#define VIX_CONTENTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_stringutil.h>
#include <vix_texture.h>
#include <vix_debugutil.h>
#include <vix_gltexture.h>
#include <vix_bmfont.h>
#include <vix_manager.h>
#include <map>



namespace Vixen {

	class IContent;

	class VIX_API ContentManager : public IManager, INonCopy
	{
	  typedef std::map<UString, IContent*> ContentMap;
	public:
		ContentManager();

		~ContentManager();

		template <typename T>
		T* Load(const UString& path);

		BMFont*  LoadFont(const UString& path);
		Texture* LoadTexture(const UString& path);

		void DumpTextures();

		ErrCode VStartUp()   override;

		ErrCode VShutDown()  override;

	private:
		ContentMap  m_textures;
		ContentMap  m_fonts;
		ContentMap  m_sounds;
	};

	template <typename T>
	  T* ContentManager::Load(const UString& path)
	  {
	    return NULL;
	  }

}

#endif
