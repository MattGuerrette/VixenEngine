#ifndef VIX_MODELCOMPONENT_H
#define VIX_MODELCOMPONENT_H

#include <vix_platform.h>
#include <vix_rendercomponent.h>
#include <vix_model.h>
#include <vix_material.h>

namespace Vixen {

	class VIX_API ModelComponent : public IRenderComponent, public IComponent
	{
	public:
		ModelComponent();

		void VOnInit();

		void VOnEnable();

		void VUpdate();

		void VOnDisable();

		void VOnDestroy();

		void VBindParent(GameObject* parent);

		IComponent::Type VGetType();

		void VSetType(IComponent::Type type);

		void VRender(ICamera3D* camera);

		void SetModel(IModel* model);
		void SetMaterial(IMaterial* material);

		IModel*		GetModel();
		IMaterial*	GetMaterial();

	private:
		IModel*				m_model;
		IMaterial*			m_material;
		IComponent::Type	m_type;
		GameObject*			m_parent;
	};

}

#endif