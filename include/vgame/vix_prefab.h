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

		std::vector<IComponent*>    m_components;
		std::vector<Prefab*>		m_children;

		uint32_t                    m_refCount;
	};

}

#endif