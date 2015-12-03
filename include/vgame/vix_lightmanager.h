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

		static void RegisterLight(Light* light, MATRIX* transform);

		static void RenderLights(ICamera3D* camera);

		static void ClearLights();

	private:
		std::vector<Light*> m_lights;
		Model*				m_lightModel;
		Material*			m_lightMaterial;
		
	};

}

#endif