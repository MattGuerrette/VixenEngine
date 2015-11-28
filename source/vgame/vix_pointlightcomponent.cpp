#include <vix_pointlightcomponent.h>

namespace Vixen {

    PointLightComponent::PointLightComponent()
        : Component(Type::POINT_LIGHT)
    {

    }

    void PointLightComponent::VOnInit()
    {
    }

    void PointLightComponent::VOnEnable()
    {
    }

    void PointLightComponent::VUpdate()
    {
    }

    void PointLightComponent::VOnDisable()
    {
    }

    void PointLightComponent::VOnDestroy()
    {
    }

    void PointLightComponent::VRender(ICamera3D* camera)
    {

    }

    void PointLightComponent::SetColor(Color color)
    {
        m_light.color = color;
    }

    void PointLightComponent::SetRange(float range)
    {
        m_light.attenuation.range = range;
    }

    void PointLightComponent::SetAttenuation(Attenuation attenuation)
    {
        m_light.attenuation = attenuation;
    }

    void PointLightComponent::SetAttenuationRange(float range)
    {
    }

    void PointLightComponent::SetAttenuationConstant(float constant)
    {
        m_light.attenuation.constant = constant;
    }

    void PointLightComponent::SetAttenuationLinear(float linear)
    {
        m_light.attenuation.linear = linear;
    }

    void PointLightComponent::SetAttenuationQuadratic(float quadratic)
    {
        m_light.attenuation.quadratic = quadratic;
    }

}