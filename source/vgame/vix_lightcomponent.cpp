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

#include <vix_lightcomponent.h>
#include <vix_gameobject.h>

namespace Vixen {
	LightComponent::LightComponent(ILight* light) : Component(Type::LIGHT)
	{
		m_light = light;
	}

	LightComponent::~LightComponent()
	{
		delete m_light;
	}

	void LightComponent::VOnInit()
	{

	}

	void LightComponent::VOnEnable()
	{

	}

	void LightComponent::VUpdate()
	{

	}

	void LightComponent::VOnDisable()
	{

	}

	void LightComponent::VOnDestroy()
	{

	}
}
