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

#ifndef VIX_LUAENGINE_H
#define VIX_LUAENGINE_H

#include <vix_platform.h>
#include <vix_lua.h>
#include <vix_singleton.h>
#include <vix_stringutil.h>
#include <vix_file.h>

namespace Vixen {

    class VIX_API LuaEngine : public Singleton<LuaEngine>
    {
    public:
        /*lua state object*/
        lua_State* m_L;
    public:
        static lua_State* L();

        /*Initialize Lua script engine*/
        static bool Initialize();

        /*DeInitialize Lua script engine*/
        static bool DeInitialize();

        /*Execute Lua script file*/
        static bool ExecuteFile(UString filePath);

        /*Execute Lua expression*/
        static bool ExecuteExpression(UString expression);

    private:
        /*report errors in evaluated lua scripts*/
        static bool ReportScriptErrors(int state);
    };

}

#endif
