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


		PointLight GetLight();

		void SetLight(PointLight light);
		void SetColor(Color color);
		void SetRange(float range);
		void SetAttenuation(Attenuation att);
		void SetAttenuationRange(float range);
		void SetAttenuationConstant(float constant);
		void SetAttenuationLinear(float linear);
		void SetAttenuationQuadratic(float quadratic);

	private:
		PointLight m_light;
	};

}

#endif