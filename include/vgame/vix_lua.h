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

#ifndef VIX_LUA_H
#define VIX_LUA_H

/*include Lua headers*/

#ifdef VIX_NOEXTERN_LUA
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#else
extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#endif

#include <LuaIntf/LuaIntf.h>


namespace Vixen {

}

#endif
