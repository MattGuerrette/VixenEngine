#include <vix_spotlightcomponent.h>
#include <vix_lightmanager.h>
#include <vix_gameobject.h>

namespace Vixen {

	SpotLightComponent::SpotLightComponent()
		: Component(Type::SPOT_LIGHT)
	{

	}

	void SpotLightComponent::VOnInit()
	{

	}

	void SpotLightComponent::VOnEnable()
	{

	}

	void SpotLightComponent::VUpdate()
	{
		m_light.position = m_parent->GetTransform()->GetWorldPosition();
	}

	void SpotLightComponent::VOnDisable()
	{

	}

	void SpotLightComponent::VOnDestroy()
	{

	}

	void SpotLightComponent::VRender(ICamera3D* camera)
	{
		LightManager::RegisterSpotLight(&m_light, m_parent->GetTransform()->GetWorldMatrix());
	}

	SpotLight SpotLightComponent::GetLight()
	{
		return m_light;
	}

	void SpotLightComponent::SetLight(SpotLight light)
	{
		m_light = light;
	}

	void SpotLightComponent::SetColor(Color color)
	{
		m_light.color = color;
	}

	void SpotLightComponent::SetRange(float range)
	{
		m_light.range = range;
	}

	void SpotLightComponent::SetConstant(float constant)
	{
		m_light.constant = constant;
	}

	void SpotLightComponent::SetLinear(float linear)
	{
		m_light.linear = linear;
	}

	void SpotLightComponent::SetQuadratic(float quadratic)
	{
		m_light.quadratic = quadratic;
	}

}