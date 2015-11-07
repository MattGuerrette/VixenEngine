#ifndef VIX_MODELCOMPONENT_H
#define VIX_MODELCOMPONENT_H

#include <vix_platform.h>
#include <vix_rendercomponent.h>
#include <vix_model.h>
#include <vix_material.h>

namespace Vixen {

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