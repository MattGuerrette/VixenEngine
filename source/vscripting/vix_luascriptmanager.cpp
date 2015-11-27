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


#include <vix_luascriptmanager.h>

namespace Vixen {


	LuaScriptManager::LuaScriptManager()
	{

	}

	LuaScriptManager::~LuaScriptManager()
	{

	}

	LuaEngine* const LuaScriptManager::Engine()
	{
		return m_engine;
	}

	ErrCode LuaScriptManager::VStartUp()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*create lua engine*/
		m_engine = new LuaEngine;


		return error;
	}

	ErrCode LuaScriptManager::VShutDown()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*destroy lua engine*/
		delete m_engine;

		return error;
	}

}
