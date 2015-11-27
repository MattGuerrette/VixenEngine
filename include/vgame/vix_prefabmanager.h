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
		static Prefab*					LoadFile(UString file);
		static Prefab*					ParsePrefab(const tinyxml2::XMLElement* element);
		static void						ParseTransform(Prefab* prefab, const tinyxml2::XMLElement* element);
		static void                     ParseComponents(Prefab* prefab, const tinyxml2::XMLElement* element);

		static Component*				ParseCameraComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseLightComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseLuaScriptComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseUITextComponent(const tinyxml2::XMLElement* element);
		static Component*               ParseModelComponent(const tinyxml2::XMLElement* element);

	private:
		PrefabMap  m_prefabs;
	};

}

#endif
