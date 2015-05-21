/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

