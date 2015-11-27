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
