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