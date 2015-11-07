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

#ifndef VIX_LUASCRIPT_H
#define VIX_LUASCRIPT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_file.h>
#include <vix_lua.h>

namespace Vixen {
	class GameObject;

    class VIX_API LuaScript : public Component
    {
		static LuaIntf::LuaRef* s_ThisTable;
    public:
        LuaScript();

        ~LuaScript();


        void SetID(UString id);
		void SetPath(UString path);

		UString GetPath();

		void BindOnInitFunction(LuaIntf::LuaRef* _func);
		void BindOnEnableFunction(LuaIntf::LuaRef* _func);
        void BindUpdateFunction(LuaIntf::LuaRef* _func);
		void BindOnDisableFunction(LuaIntf::LuaRef* _func);
		void BindOnDestroyFunction(LuaIntf::LuaRef* _func);

		void SetObject();
		
		void VOnInit();
		void VOnEnable();
        void VUpdate();
		void VOnDisable();
		void VOnDestroy();

        void VBindParent(GameObject* parent);

    private:
        UString             m_id;
		UString				m_path;
		std::string	        m_tablePath;
		LuaIntf::LuaRef     m_table;

		//function in lua references
		LuaIntf::LuaRef*    m_onInitFunc;
		LuaIntf::LuaRef*    m_onEnableFunc;
        LuaIntf::LuaRef*    m_updateFunc;
		LuaIntf::LuaRef*    m_onDisableFunc;
		LuaIntf::LuaRef*    m_onDestroyFunc;
    };

}

#endif
