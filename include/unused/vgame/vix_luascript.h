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

#ifndef VIX_LUASCRIPT_H
#define VIX_LUASCRIPT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_file.h>
#include <vix_lua.h>

namespace Vixen {
	class GameObject;

    class VIX_API LuaScript : public Component
    {
		static LuaIntf::LuaRef* s_ThisTable;
    public:
        LuaScript();

        ~LuaScript();


        void SetID(UString id);
		void SetPath(UString path);

		UString GetPath();

		void BindOnInitFunction(LuaIntf::LuaRef* _func);
		void BindOnEnableFunction(LuaIntf::LuaRef* _func);
        void BindUpdateFunction(LuaIntf::LuaRef* _func);
		void BindOnDisableFunction(LuaIntf::LuaRef* _func);
		void BindOnDestroyFunction(LuaIntf::LuaRef* _func);

		void SetObject();

		void VOnInit();
		void VOnEnable();
        void VUpdate();
		void VOnDisable();
		void VOnDestroy();

        void VBindParent(GameObject* parent);

    private:
        UString             m_id;
		UString				m_path;
		std::string	        m_tablePath;
		LuaIntf::LuaRef     m_table;

		//function in lua references
		LuaIntf::LuaRef*    m_onInitFunc;
		LuaIntf::LuaRef*    m_onEnableFunc;
        LuaIntf::LuaRef*    m_updateFunc;
		LuaIntf::LuaRef*    m_onDisableFunc;
		LuaIntf::LuaRef*    m_onDestroyFunc;
    };

}

#endif
