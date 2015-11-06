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

#ifndef VIX_PREFAB_H
#define VIX_PREFAB_H

#include <vix_platform.h>
#include <vix_containers.h>
#include <vix_transform.h>
#include <vix_stringutil.h>
#include <vix_gameobject.h>

namespace Vixen {

	class Prefab
	{
	public:
		Prefab();

		~Prefab();

		std::string GetName();
		bool        GetEnabled();
		Transform   GetTransform();
		std::string GetModelFile();

		void SetName(std::string name);
		void SetEnabled(bool enabled);
		void SetTransform(Transform t);
		void SetModelFile(std::string file);

		void AddChild(Prefab* child);
		void AddComponent(Component* component);
		void AddScriptFile(std::string file);

		GameObject* CreateObject();

		void IncRefCount();
		void DecRefCount();
		uint32_t RefCount();

		size_t ScriptCount();
		size_t ChildCount();

		Prefab* GetChild(int index);
		std::string GetScriptFile(int index);

	private:
		static GameObject* BuildFromPrefab(Prefab* prefab);

	private:
		std::string					m_name;
		bool						m_enabled;
		Transform					m_transform;
		std::string				    m_modelFile;

		std::vector<std::string>    m_scriptFiles;

		std::vector<Component*>    m_components;
		std::vector<Prefab*>		m_children;

		uint32_t                    m_refCount;
	};

}

#endif
