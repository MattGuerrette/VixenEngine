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

#include <vix_luascript.h>
#include <vix_luaengine.h>
#include <vix_luascriptmanager.h>
#include <vix_gameobject.h>

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

	void LuaScript::VUpdate(float dt)
	{
		SetObject();

		LuaScriptManager::PushScript(this);

        try
        {
           m_updateFunc->call(dt);
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