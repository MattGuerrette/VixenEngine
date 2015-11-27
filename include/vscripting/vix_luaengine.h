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
#include <vix_scriptengine.h>
#include <vix_lua.h>
#include <vix_singleton.h>

namespace Vixen {

	class VIX_API LuaEngine : public Singleton<LuaEngine>, public IScriptEngine
	{
		/*lua state object*/
		lua_State* m_L;
	public:
		lua_State* L();

        /*Initialize Lua script engine*/
        bool VInitialize() override;

        /*DeInitialize Lua script engine*/
        bool VDeInitialize() override;

		/*Execute Lua script file*/
		ErrCode VExecuteFile(const UString& path) override;

		/*Execute Lua expression*/
		ErrCode VExecuteExpression(const UString& expression) override;

	private:
		/*report errors in evaluated lua scripts*/
		ErrCode ReportScriptErrors(int state);
	};

}

#endif
