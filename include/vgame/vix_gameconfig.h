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

#ifndef VIX_GAMECONFIG_H
#define VIX_GAMECONFIG_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_stringutil.h>
#include <vix_tinyxml.h>
#include <vix_sdlwindow.h>

namespace Vixen {

	class VIX_API GameConfig : public INonCopy
	{
	public:
		GameConfig();

		/*Accessors for loaded data*/

		SDL_GW_Params WindowArgs() const;

	private:
		bool          LoadConfig();
		bool          ParseConfig(const XMLDOC& doc);
		SDL_GW_Params ParseWindow(const XMLDOC& doc);

	private:
		SDL_GW_Params m_windowArgs;
		UString       m_path;
	};
}

#endif
