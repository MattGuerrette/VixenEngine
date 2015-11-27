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

#ifndef VIX_MODELCOMPONENT_H
#define VIX_MODELCOMPONENT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_rendercomponent.h>
#include <vix_model.h>
#include <vix_material.h>

namespace Vixen {

    class GameObject;

	class VIX_API ModelComponent : public IRenderComponent, public Component
	{
	public:
		ModelComponent();

		void VOnInit();

		void VOnEnable();

		void VUpdate();

		void VOnDisable();

		void VOnDestroy();

		void VBindParent(GameObject* parent);

		void VRender(ICamera3D* camera);

		void SetModel(Model* model);
		void SetMaterial(Material* material);

		Model*		GetModel();
		Material*	GetMaterial();

	private:
		Model*				m_model;
		Material*			m_material;
		GameObject*			m_parent;
	};

}

#endif
