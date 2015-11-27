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

#ifndef VIX_LUASCRIPTMANAGER_H
#define VIX_LUASCRIPTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_luaengine.h>
#include <vix_manager.h>

namespace Vixen {

	class VIX_API LuaScriptManager : public Singleton < LuaScriptManager >, IManager
	{
		friend class Singleton < LuaScriptManager >;

	public:
		/*constructor (NOTE: intialization occurs in VStartUp()*/
		LuaScriptManager();

		/*desturctor (NOTE: destruction occurs in VShutDown()*/
		~LuaScriptManager();

		/*Initialize LuaScriptManager*/
		ErrCode VStartUp()  override;

		/*Destruct LuaScriptManager*/
		ErrCode VShutDown() override;

		LuaEngine* const Engine();
	private:
		LuaEngine*  m_engine;
	};

	extern LuaScriptManager& g_LuaScriptManager;
}

#endif
