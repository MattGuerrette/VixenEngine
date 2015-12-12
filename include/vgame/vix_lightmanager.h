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

		static void RegisterPointLight(Light* light, MATRIX* transform);
		static void RegisterSpotLight(Light* light, MATRIX* transform);

		static void RenderLights(ICamera3D* camera);

		static void ClearLights();

		static Material* GetMaterial();

	private:
		std::vector<Light*> m_pointLights;
		std::vector<Light*> m_spotLights;
		Model*				m_pointLightModel;
		Model*				m_spotLightModel;
		Material*			m_lightMaterial;
		
	};

}

#endif