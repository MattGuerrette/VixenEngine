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

#ifndef VIX_LIGHTCOMPONENT_H
#define VIX_LIGHTCOMPONENT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_light.h>

namespace Vixen {

	class GameObject;

	class VIX_API LightComponent : public IComponent
	{
	public:
		LightComponent(ILight* light);

		~LightComponent();

		void VOnInit();

		void VOnEnable();

		void VUpdate();

		void VOnDisable();

		void VOnDestroy();

		void VBindParent(GameObject* parent);

	private:
		GameObject*         m_parent;
		//Transform*          m_parentTransform;
		ILight*				m_light;
	};

}

#endif
