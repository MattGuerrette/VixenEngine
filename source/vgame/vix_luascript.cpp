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

#include <vix_luascript.h>
#include <vix_luaengine.h>
#include <vix_luascriptmanager.h>
#include <vix_gameobject.h>
#include <vix_time.h>

namespace Vixen {

	LuaIntf::LuaRef* LuaScript::s_ThisTable = NULL;

	LuaScript::LuaScript() : Component(Type::LUA_SCRIPT)
	{
        m_onInitFunc = NULL;
        m_onDestroyFunc = NULL;
        m_onEnableFunc = NULL;
        m_onDisableFunc = NULL;
		m_updateFunc = NULL;
		m_parent = NULL;

		m_type = Component::Type::LUA_SCRIPT;
	}

	LuaScript::~LuaScript()
    {
        delete m_onInitFunc;
        delete m_onEnableFunc;
        delete m_updateFunc;
        delete m_onDisableFunc;
        delete m_onDestroyFunc;
	}

	void LuaScript::SetPath(UString path)
	{
		m_path = path;
	}

	UString LuaScript::GetPath()
	{
		return m_path;
	}

	void LuaScript::VOnInit()
	{

		//prepare for executing lua script
		//need to set active Global gameobject
		VBindParent(m_parent);

		SetObject();

		LuaScriptManager::PushScript(this);

		try
		{
			if (m_onInitFunc->isValid())
				m_onInitFunc->call();
		}
		catch (const LuaIntf::LuaException& e)
		{
			DebugPrintF(VTEXT("LuaScript Error: %s\n"), UStringFromCharArray(e.what()).c_str());
		}



		LuaScriptManager::PopScript();
		if (LuaScriptManager::PeekScript())
			LuaScriptManager::PeekScript()->SetObject();
	}

	void LuaScript::VOnEnable()
	{
		SetObject();

		LuaScriptManager::PushScript(this);

		try
		{
			if (m_onEnableFunc->isValid())
				m_onEnableFunc->call();
		}
		catch (const LuaIntf::LuaException& e)
		{
			DebugPrintF(VTEXT("LuaScript Error: %s\n"), UStringFromCharArray(e.what()).c_str());
		}



		LuaScriptManager::PopScript();

		if (LuaScriptManager::PeekScript())
			LuaScriptManager::PeekScript()->SetObject();
	}

	void LuaScript::VUpdate()
	{
		SetObject();

		GameObject::s_ActiveObject = this->m_parent;

		LuaScriptManager::PushScript(this);

		try
		{
			m_updateFunc->call(Time::DeltaTime());
		}
		catch (const LuaIntf::LuaException& e)
		{
			DebugPrintF(VTEXT("LuaScript Error: %s\n"), UStringFromCharArray(e.what()).c_str());
		}





		LuaScriptManager::PopScript();
		if (LuaScriptManager::PeekScript())
			LuaScriptManager::PeekScript()->SetObject();
	}

	void LuaScript::VOnDisable()
	{
		SetObject();

		LuaScriptManager::PushScript(this);

		if (m_onDisableFunc->isValid())
			m_onDisableFunc->call();


		LuaScriptManager::PopScript();
		if (LuaScriptManager::PeekScript())
			LuaScriptManager::PeekScript()->SetObject();
	}

	void LuaScript::VOnDestroy()
	{
		SetObject();

		LuaScriptManager::PushScript(this);

		if (m_onDestroyFunc->isValid())
			m_onDestroyFunc->call();

		s_ThisTable->set(m_tablePath, LUA_TNIL);

		LuaScriptManager::PopScript();

		if (LuaScriptManager::PeekScript())
			LuaScriptManager::PeekScript()->SetObject();
	}


	void LuaScript::BindOnInitFunction(LuaIntf::LuaRef* _func)
	{
		m_onInitFunc = _func;
	}

	void LuaScript::BindOnEnableFunction(LuaIntf::LuaRef* _func)
	{
		m_onEnableFunc = _func;
	}

	void LuaScript::BindUpdateFunction(LuaIntf::LuaRef* _func)
	{
		m_updateFunc = _func;
	}

	void LuaScript::BindOnDisableFunction(LuaIntf::LuaRef* _func)
	{
		m_onDisableFunc = _func;
	}

	void LuaScript::BindOnDestroyFunction(LuaIntf::LuaRef* _func)
	{
		m_onDestroyFunc = _func;
	}

	void LuaScript::VBindParent(GameObject* gameObject)
	{
		using namespace LuaIntf;

		if (!m_parent)
			m_parent = gameObject;

		m_tablePath = "_G." + UStringToStd(m_id) + ".hash." + std::to_string(m_parent->GetID());

		LuaBinding(LuaEngine::L())
			.beginModule(UStringToStd(m_id).c_str())
			.beginModule("hash")
			.beginModule(std::to_string(m_parent->GetID()).c_str())
			.addVariableRef("GameObject", m_parent)
			.endModule()
			.endModule()
			.endModule();

		m_table = LuaRef(LuaEngine::L(), m_tablePath.c_str());

	}

	void LuaScript::SetObject()
	{
		using namespace LuaIntf;
		if (!s_ThisTable)
			s_ThisTable = new LuaRef(LuaEngine::L(), "_G");

		s_ThisTable->set("this", m_table);
	}


	void LuaScript::SetID(UString id)
	{
		m_id = id;
	}
}
