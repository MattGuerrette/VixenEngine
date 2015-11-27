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

#ifndef VIX_LUASCRIPT_H
#define VIX_LUASCRIPT_H

#include <vix_platform.h>
#include <vix_lua.h>
#include <vix_stringutil.h>
#include <vix_errglobals.h>

namespace Vixen {

	struct LuaScriptInfo
	{
		UString file;
		UString raw;
	};

	class LuaEngine;

	/* LuaScript class
	*
	*  Desc:
	*  This class describes a LuaScript object that can be attached to any
	*  gameobject in order for user to implement scripting logic in predefined
	*  functions.
	*
	*  Functions:
	*
	*  OnAwake()      - called to initialize script object before scene starts
	*
	*  OnUpdate()     - called every frame during game update
	*
	*  OnLateUpdate() - called after all calls to Update have been processed
	*/
	class VIX_API LuaScript
	{
		typedef luabridge::LuaRef LuaRef;
		/*CONTANTS*/
	public:
		static const UString OBJECT_TABLE;
		static const UString AWAKE_FUNC;
		static const UString UPDATE_FUNC;
		static const UString LATEUPDATE_FUNC;
		static const UString AWAKE_FULL_SIGN;
		static const UString UPDATE_FULL_SIGN;
		static const UString LATEUPDATE_FULL_SIGN;

	public:
		LuaScript(LuaScriptInfo info);

		~LuaScript();

		/*load script file*/
		ErrCode Load(LuaEngine* engine, LuaScriptInfo info);

		/*get script info*/
		LuaScriptInfo Info();

		/*awake*/
		ErrCode Awake();

		/*update*/
		ErrCode Update();

		/*late update*/
		ErrCode LateUpdate();

	private:
		LuaScriptInfo      m_info;
		LuaRef*            m_awakeFunc;
		LuaRef*            m_updateFunc;
		LuaRef*            m_lateUpdateFunc;

		ErrCode InitFuncRefs(LuaEngine* engine);
	};

}

#endif
