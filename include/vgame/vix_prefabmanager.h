/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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

#ifndef VIX_PREFABMANAGER_H
#define VIX_PREFABMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_containers.h>
#include <vix_prefab.h>
#include <vix_tinyxml.h>

namespace Vixen {

	class VIX_API PrefabManager : public Singleton<PrefabManager>
	{
		typedef std::map<UString, Prefab*> PrefabMap;
	public:

		static bool		Initialize();

		static void		DeInitialize();

		static Prefab*	Load(std::string file);

		static Prefab*	GetPrefab(UString file);

		static void     Cleanup();

	private:
		static Prefab* LoadFile(UString file);
		static Prefab* ParsePrefab(const tinyxml2::XMLElement* element);

	private:
		PrefabMap  m_prefabs;
	};

}

#endif