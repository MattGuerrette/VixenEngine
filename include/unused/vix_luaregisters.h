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
