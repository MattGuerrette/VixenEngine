#ifndef VIX_POINTLIGHTCOMPONENT_H
#define VIX_POINTLIGHTCOMPONENT_H

#include "vix_platform.h"
#include "vix_component.h"
#include "vix_rendercomponent.h"
#include "vix_light.h"

namespace Vixen {

    class VIX_API PointLightComponent : public Component, public IRenderComponent
    {
    public:
        PointLightComponent();

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
        void SetConstant(float constant);
        void SetLinear(float linear);
        void SetQuadratic(float quadratic);

    private:
        PointLight m_light;
    };

}

#endif