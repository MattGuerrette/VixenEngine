/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vix_luascript.h>
#include <vix_luaengine.h>
#include <vix_luascriptmanager.h>
#include <vix_gameobject.h>
#include <vix_time.h>

namespace Vixen {

	LuaIntf::LuaRef* LuaScript::s_ThisTable = NULL;

    LuaScript::LuaScript()
    {
        m_updateFunc = NULL;
        m_parent = NULL;
    }

    LuaScript::~LuaScript()
    {
        delete m_updateFunc;
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


		LuaScriptManager::PopScript();

		//when we destroy the script, also delete pointers
		delete m_onInitFunc;
		delete m_onEnableFunc;
		delete m_updateFunc;
		delete m_onDisableFunc;
		delete m_onDestroyFunc;

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

        if(!m_parent)
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
