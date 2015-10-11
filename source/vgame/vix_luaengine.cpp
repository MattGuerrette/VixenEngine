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

#include <vix_luaengine.h>
#include <vix_debugutil.h>

namespace Vixen {

    bool LuaEngine::Initialize()
    {
        LuaEngine& _engine = LuaEngine::instance();

        _engine.m_L = luaL_newstate();

        luaL_openlibs(_engine.m_L);

        return true;
    }

    bool LuaEngine::DeInitialize()
    {
        LuaEngine& _engine = LuaEngine::instance();

        lua_close(_engine.m_L);

        return true;
    }

    lua_State* LuaEngine::L()
    {
        LuaEngine& _engine = LuaEngine::instance();

        return _engine.m_L;
    }

    bool LuaEngine::ReportScriptErrors(int state)
    {
        LuaEngine& _engine = LuaEngine::instance();

        if (state != 0) {
            const char* err = lua_tostring(_engine.m_L, state);

			if (err) {
				DebugPrintF(VTEXT("Lua Script Error: %s"),
					UStringFromCharArray(err).c_str());
				lua_pop(_engine.m_L, 1); //remove error
			}
            return false;
        }

        return true;
    }

    bool LuaEngine::ExecuteFile(UString filePath)
    {
        LuaEngine& _engine = LuaEngine::instance();

        if (filePath.empty()) {
            DebugPrintF(VTEXT("Failed to execute script file: NULL PATH"));
            return false;
        }

        /*try and execute script file*/
        std::string _path = UStringToStd(filePath);
        int state = luaL_dofile(_engine.m_L, _path.c_str());
        if (!LuaEngine::ReportScriptErrors(state)) {
            DebugPrintF(VTEXT("Failed to execute script file"));
            return false;
        }

        return true;
    }

    bool LuaEngine::ExecuteExpression(UString expression)
    {
        LuaEngine& _engine = LuaEngine::instance();

        if (expression.empty()) {
            DebugPrintF(VTEXT("SCRIPT EMPTY"));
            return false;
        }

        std::string _exp = UStringToStd(expression);
        int state = luaL_dostring(_engine.m_L, _exp.c_str());
        if (!ReportScriptErrors(state)) {
            DebugPrintF(VTEXT("Failed to execute script expression"));
            return false;
        }

        return true;
    }
}
