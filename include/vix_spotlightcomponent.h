#ifndef VIX_SPOTLIGHTCOMPONENT_H
#define VIX_SPOTLIGHTCOMPONENT_H

#include "vix_platform.h"
#include "vix_component.h"
#include "vix_rendercomponent.h"
#include "vix_light.h"

namespace Vixen {

	class VIX_API SpotLightComponent : public Component, public IRenderComponent
	{
	public:
		SpotLightComponent();

		void VOnInit();
		void VOnEnable();
		void VUpdate();
		void VOnDisable();
		void VOnDestroy();

		void VRender(ICamera3D* camera);


		SpotLight GetLight();

		void SetLight(SpotLight light);
		void SetColor(Color color);
		void SetRange(float range);
		void SetAngle(float angle);
		void SetConstant(float constant);
		void SetLinear(float linear);
		void SetQuadratic(float quadratic);

	private:
		SpotLight m_light;
	};

}

#endif