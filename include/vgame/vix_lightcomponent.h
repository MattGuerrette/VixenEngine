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

#ifndef VIX_LIGHTCOMPONENT_H
#define VIX_LIGHTCOMPONENT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_light.h>

namespace Vixen {

	class GameObject;

	class VIX_API LightComponent : public Component
	{
	public:
		LightComponent(ILight* light);

		~LightComponent();

		void VOnInit();

		void VOnEnable();

		void VUpdate();

		void VOnDisable();

		void VOnDestroy();

	private:
		//Transform*          m_parentTransform;
		ILight*				m_light;
	};

}

#endif
