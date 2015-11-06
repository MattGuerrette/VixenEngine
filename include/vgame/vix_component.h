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

	class VIX_API Component
	{
	public:

		enum class Type
		{
			UNUSED,
			LUA_SCRIPT,
			LIGHT,
			UI_TEXT,
			UI_BUTTON,
			UI_TEXTURE,
			SPRITE
		};

		Component(Type type)
		{
			m_type = type;
		}

		virtual ~Component() { };
		virtual void VOnInit() = 0;
		virtual void VOnEnable() = 0;
		virtual void VUpdate() = 0;
		virtual void VOnDisable() = 0;
		virtual void VOnDestroy() = 0;
<<<<<<< HEAD
        virtual void VBindParent(GameObject* parent) = 0;

=======

		virtual void VBindParent(GameObject* parent)
		{
			m_parent = parent;
		}


		virtual Component::Type VGetType()
		{
			return m_type;
		}

	protected:
		GameObject* m_parent;
		Type		m_type;
>>>>>>> 5d61730afc80281f2da012a8e50084e490f8a879
	};

}

#endif
