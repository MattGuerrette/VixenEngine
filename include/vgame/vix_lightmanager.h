#ifndef VIX_LIGHTMANAGER_H
#define VIX_LIGHTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_light.h>
#include <vix_model.h>

namespace Vixen {

	class VIX_API LightManager : public Singleton<LightManager>
	{
	public:
		static void Initialize();
		
		static void DeInitialize();

		static void RegisterPointLight(PointLight* light, MATRIX* transform);
		static void RegisterSpotLight(SpotLight* light, MATRIX* transform);

		static void RenderLights(ICamera3D* camera);

		static void ClearLights();

		static Material* GetMaterial();

	private:
		std::vector<PointLight*> m_pointLights;
		std::vector<SpotLight*> m_spotLights;
		Model*				m_pointLightModel;
		Model*				m_spotLightModel;
		Material*			m_pointLightMaterial;
		Material*			m_spotLightMaterial;
		
	};

}

#endif