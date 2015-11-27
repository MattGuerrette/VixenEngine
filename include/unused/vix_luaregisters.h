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

#ifndef VIX_LUAREGISTERS_H
#define VIX_LUAREGISTERS_H

#include <vix_platform.h>
#include <vix_lua.h>

/*
*	Lua Register Header
*   Desc:
*   This header contains static register function definitions
*   for each type of object that will be exposed to Lua and scriptable
*   by the developer
*/

namespace Vixen {

	VIX_API void RegisterLuaObjects(lua_State* L);
	VIX_API void RegisterSoundClip(lua_State* L);
}

#endif
