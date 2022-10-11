
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

#include <vix_modelcomponent.h>
#include "vix_resourcemanager.h"
#include <vix_gameobject.h>

namespace Vixen {

	ModelComponent::ModelComponent()
		: Component(Component::Type::MODEL)
	{
		m_material = nullptr;
		m_model = nullptr;
	}

	void ModelComponent::VOnInit()
	{

	}

	void ModelComponent::VOnEnable()
	{

	}

	void ModelComponent::VOnDisable()
	{

	}

	void ModelComponent::VOnDestroy()
	{
		ResourceManager::DecrementAssetRef(m_model);
		ResourceManager::DecrementAssetRef(m_material);
	}

	void ModelComponent::VUpdate()
	{

	}

	void ModelComponent::VRender(ICamera3D* camera)
	{
		if (m_model)
			m_model->VBatchRender(m_parent->GetTransform()->GetWorldMatrix());
	}

	void ModelComponent::VBindParent(GameObject* parent)
	{
		m_parent = parent;
	}

	void ModelComponent::SetModel(Model* model)
	{
		m_model = model;
	}

	void ModelComponent::SetMaterial(Material* material)
	{
		m_material = material;
		if (m_model)
			m_model->VSetMaterial(m_material);
	}

	Model* ModelComponent::GetModel()
	{
		return m_model;
	}

	Material* ModelComponent::GetMaterial()
	{
		return m_material;
	}
}

