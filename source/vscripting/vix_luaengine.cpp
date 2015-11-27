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

#include <vix_luaengine.h>
#include <vix_debugutil.h>

namespace Vixen {

	//LuaEngine::LuaEngine()
	//{
	//	/*create luastate handle*/
	//	m_L = luaL_newstate();
	//	/*open standard lua libraries*/
	//	luaL_openlibs(m_L);
	//}

    bool LuaEngine::VInitialize()
    {
        m_L = luaL_newstate();

        luaL_openlibs(m_L);

        return true;
    }

    bool LuaEngine::VDeInitialize()
    {
        /*close lua state object*/
        lua_close(m_L);

        return true;
    }

	lua_State* LuaEngine::L()
	{
		return m_L;
	}

	ErrCode LuaEngine::ReportScriptErrors(int state)
	{
		if (state != 0) {
            const char* err = lua_tostring(m_L, state);

			DebugPrintF(VTEXT("Lua Script Error: %s"),
                UStringFromCharArray(err).c_str());
			lua_pop(m_L, 1); //remove error
			return ErrCode::ERR_FAILURE;
		}

		return ErrCode::ERR_SUCCESS;
	}

	ErrCode LuaEngine::VExecuteFile(const UString& path)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		if (path.empty()) {
			DebugPrintF(VTEXT("Failed to execute script file: NULL PATH"));
			return ErrCode::ERR_NULL_PATH;
		}

		/*try and execute script file*/
        std::string _path = UStringToStd(path);
		int state = luaL_dofile(m_L, _path.c_str());
		error = ReportScriptErrors(state);
		if (CheckError(error)) {
                        DebugPrintF(VTEXT("Failed to execute script file"));
		}
		return error;
	}

	ErrCode LuaEngine::VExecuteExpression(const UString& expression)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		if (expression.empty()) {
			DebugPrintF(VTEXT("SCRIPT EMPTY"));
			return ErrCode::ERR_NULL_PATH;
		}

        std::string _exp = UStringToStd(expression);
		int state = luaL_dostring(m_L, _exp.c_str());
		error = ReportScriptErrors(state);
		if (CheckError(error)) {
                        DebugPrintF(VTEXT("Failed to execute script expression"));
		}

		return error;
	}


}
