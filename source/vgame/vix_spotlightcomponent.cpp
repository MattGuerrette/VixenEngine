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

	PointLight SpotLightComponent::GetLight()
	{
		return m_light;
	}

	void SpotLightComponent::SetLight(PointLight light)
	{
		m_light = light;
	}

	void SpotLightComponent::SetColor(Color color)
	{
		m_light.color = color;
	}

	void SpotLightComponent::SetRange(float range)
	{
		m_light.attenuation.range = range;
	}

	void SpotLightComponent::SetAttenuation(Attenuation attenuation)
	{
		m_light.attenuation = attenuation;
	}

	void SpotLightComponent::SetAttenuationRange(float range)
	{
		m_light.attenuation.range = range;
	}

	void SpotLightComponent::SetAttenuationConstant(float constant)
	{
		m_light.attenuation.constant = constant;
	}

	void SpotLightComponent::SetAttenuationLinear(float linear)
	{
		m_light.attenuation.linear = linear;
	}

	void SpotLightComponent::SetAttenuationQuadratic(float quadratic)
	{
		m_light.attenuation.quadratic = quadratic;
	}

}