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