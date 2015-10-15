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

#ifndef VIX_LUASCRIPTMANAGER_H
#define VIX_LUASCRIPTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_luascript.h>
#include <stack>

namespace Vixen {

    class VIX_API LuaScriptManager : public Singleton<LuaScriptManager>
    {
    public:
		static void Initialize();
        static LuaScript* LoadScript(UString name);
		static LuaIntf::LuaRef* s_thisTable;

		static void PushScript(LuaScript* script);
		static LuaScript* PeekScript();
		static void PopScript();

	private:
		static std::stack<LuaScript*> m_scriptStack;
		static void BindLuaObjects();
    };

}

#endif
