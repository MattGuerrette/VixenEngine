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
#include <vix_paths.h>
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
