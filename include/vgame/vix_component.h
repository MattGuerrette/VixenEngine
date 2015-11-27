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
			SPRITE,
			MODEL,
			CAMERA,
			PHYSICS_RIGIDBODY
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
	};

}

#endif
