#ifndef VIX_POINTLIGHTCOMPONENT_H
#define VIX_POINTLIGHTCOMPONENT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_rendercomponent.h>
#include <vix_light.h>

namespace Vixen {

    class VIX_API PointLightComponent : public Component
    {
    public:
        PointLightComponent();

        void VOnInit();
        void VOnEnable();
        void VUpdate();
        void VOnDisable();
        void VOnDestroy();

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