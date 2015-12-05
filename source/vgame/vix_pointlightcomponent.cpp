#include <vix_pointlightcomponent.h>
#include <vix_lightmanager.h>
#include <vix_gameobject.h>

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
		//LightManager::RegisterLight(&m_light, m_parent->GetTransform()->GetWorldMatrix());
    }

    void PointLightComponent::VUpdate()
    {
		m_light.position = m_parent->GetTransform()->GetWorldPosition();
    }

    void PointLightComponent::VOnDisable()
    {
		DebugPrintF(VTEXT("PointLight disabled\n"));
    }

    void PointLightComponent::VOnDestroy()
    {
		DebugPrintF(VTEXT("PointLight destroyed\n"));
    }

	void PointLightComponent::VRender(ICamera3D* camera)
	{
		LightManager::RegisterLight(&m_light, m_parent->GetTransform()->GetWorldMatrix());
	}

	PointLight PointLightComponent::GetLight()
	{
		return m_light;
	}

	void PointLightComponent::SetLight(PointLight light)
	{
		m_light = light;
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
        m_light.attenuation.range = range;
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