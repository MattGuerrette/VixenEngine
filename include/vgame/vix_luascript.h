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
