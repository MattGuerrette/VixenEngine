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
