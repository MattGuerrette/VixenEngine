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
