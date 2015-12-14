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
		
    }

    void PointLightComponent::VUpdate()
    {
		m_light.position = m_parent->GetTransform()->GetWorldPosition();
    }

    void PointLightComponent::VOnDisable()
    {
		
    }

    void PointLightComponent::VOnDestroy()
    {
		
    }

	void PointLightComponent::VRender(ICamera3D* camera)
	{
		LightManager::RegisterPointLight(&m_light, m_parent->GetTransform()->GetWorldMatrix());
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
        m_light.range = range;
    }

    void PointLightComponent::SetConstant(float constant)
    {
        m_light.constant = constant;
    }

    void PointLightComponent::SetLinear(float linear)
    {
        m_light.linear = linear;
    }

    void PointLightComponent::SetQuadratic(float quadratic)
    {
        m_light.quadratic = quadratic;
    }

}