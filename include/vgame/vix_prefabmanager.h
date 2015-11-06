/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
		static Prefab*					LoadFile(UString file);
		static Prefab*					ParsePrefab(const tinyxml2::XMLElement* element);
		static void						ParseTransform(Prefab* prefab, const tinyxml2::XMLElement* element);
		static void                     ParseComponents(Prefab* prefab, const tinyxml2::XMLElement* element);
		static Component*				ParseCameraComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseLightComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseLuaScriptComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseUITextComponent(const tinyxml2::XMLElement* element);


	private:
		PrefabMap  m_prefabs;
	};

}

#endif
