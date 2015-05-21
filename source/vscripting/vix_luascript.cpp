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


#include <vix_luascript.h>
#include <vix_debugutil.h>
#include <vix_luaengine.h>

namespace Vixen {

	const UString LuaScript::OBJECT_TABLE = VTEXT("_GO");
	const UString LuaScript::AWAKE_FUNC = VTEXT("OnAwake");
	const UString LuaScript::UPDATE_FUNC = VTEXT("OnUpdate");
	const UString LuaScript::LATEUPDATE_FUNC = VTEXT("OnLateUpdate");
	const UString LuaScript::AWAKE_FULL_SIGN = LuaScript::OBJECT_TABLE +
		VTEXT(".") +
		LuaScript::AWAKE_FUNC;
	const UString LuaScript::UPDATE_FULL_SIGN = LuaScript::OBJECT_TABLE +
		VTEXT(".") +
		LuaScript::UPDATE_FUNC;
	const UString LuaScript::LATEUPDATE_FULL_SIGN = LuaScript::OBJECT_TABLE +
		VTEXT(".") +
		LuaScript::LATEUPDATE_FUNC;


	LuaScript::LuaScript(LuaScriptInfo info)
	{
		m_info = info;
		m_awakeFunc = NULL;
		m_updateFunc = NULL;
		m_lateUpdateFunc = NULL;
	}

	LuaScript::~LuaScript()
	{
		delete m_awakeFunc;
		delete m_updateFunc;
		delete m_lateUpdateFunc;
	}

	ErrCode LuaScript::Load(LuaEngine* engine, LuaScriptInfo info)
	{
		if (!engine) {
			DebugPrintF(VTEXT("Error loading LuaScript [No engine]: %s\n"));
			return ErrCode::ERR_FAILURE;
		}

		if (info.file.empty() && info.raw.empty()) {
			DebugPrintF(VTEXT("Error loading LuaScript [No contents]: %s\n"));
			return ErrCode::ERR_FAILURE;
		}

		/*load script file*/
		if (!info.file.empty())
		{
			//engine->VExecuteFile(info.file);
		}
		/*load raw script expression*/
		else
		{
			//engine->VExecuteExpression(info.raw);
		}

		/*store lua function reference*/
		return InitFuncRefs(engine);
	}

	ErrCode LuaScript::InitFuncRefs(LuaEngine* engine)
	{
#ifdef UNICODE && VIX_SYS_WINDOWS
		UConverter cv;
		std::string _awake = cv.to_bytes(AWAKE_FULL_SIGN);
		std::string _update = cv.to_bytes(UPDATE_FULL_SIGN);
		std::string _lateUpdate = cv.to_bytes(LATEUPDATE_FULL_SIGN);
#else
		std::string _awake = AWAKE_FULL_SIGN;
		std::string _update = UPDATE_FULL_SIGN;
		std::string _lateUpdate = LATEUPDATE_FULL_SIGN;
#endif
		m_awakeFunc = new LuaRef(engine->L(), _awake.c_str());
		m_updateFunc = new LuaRef(engine->L(), _update.c_str());
		m_lateUpdateFunc = new LuaRef(engine->L(), _lateUpdate.c_str());
		if (!m_awakeFunc ||
			!m_updateFunc ||
			!m_lateUpdateFunc)
		{
			DebugPrintF(VTEXT("Error Initiliazing Ref Funcs: %s\n"));
			return ErrCode::ERR_FAILURE;
		}

		return ErrCode::ERR_SUCCESS;
	}

	ErrCode LuaScript::Awake()
	{
		if (!m_awakeFunc) {
			DebugPrintF(VTEXT("Error calling Awake(). Null function\n%s\n"));
			return ErrCode::ERR_FAILURE;
		}

		(*m_awakeFunc)();
	}

	ErrCode LuaScript::Update()
	{
		if (!m_updateFunc) {
			DebugPrintF(VTEXT("Error calling Update(). Null function\n%s\n"));
			return ErrCode::ERR_FAILURE;
		}

		(*m_updateFunc)();
	}

	ErrCode LuaScript::LateUpdate()
	{
		if (!m_lateUpdateFunc) {
			DebugPrintF(VTEXT("Error calling LateUpdate(). Null function\n%s\n"));
			return ErrCode::ERR_FAILURE;
		}

		(*m_lateUpdateFunc)();
	}

}
