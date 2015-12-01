#ifndef VIX_LIGHTMANAGER_H
#define VIX_LIGHTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_light.h>

namespace Vixen {

	class VIX_API LightManager : public Singleton<LightManager>
	{
	public:
		static void Initialize();
		
		static void DeInitialize();

		static void RegisterLight(Light* light);

		static void RenderLights();

	private:
		std::vector<Light*> m_lights;
	};

}

#endif