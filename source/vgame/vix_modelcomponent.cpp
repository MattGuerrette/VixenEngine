#include <vix_modelcomponent.h>

namespace Vixen {

	ModelComponent::ModelComponent()
	{
		m_type = IComponent::Type::MODEL;
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
        delete m_model;
		delete m_material;
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

	void ModelComponent::VSetType(IComponent::Type type)
	{
		m_type = type;
	}
	
	IComponent::Type ModelComponent::VGetType()
	{
		return m_type;
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