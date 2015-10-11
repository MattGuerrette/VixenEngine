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

#ifndef VIX_COMPONENT_H
#define VIX_COMPONENT_H

#include <vix_platform.h>
#include <vix_gamewindow.h>

namespace Vixen {


	class Game;
    class GameObject;

	class VIX_API IComponent
	{
	public:
		virtual ~IComponent() { };
		virtual void VOnInit() = 0;
		virtual void VOnEnable() = 0;
		virtual void VUpdate() = 0;
		virtual void VOnDisable() = 0;
		virtual void VOnDestroy() = 0;
        virtual void VBindParent(GameObject* parent) = 0;

	};

}

#endif
