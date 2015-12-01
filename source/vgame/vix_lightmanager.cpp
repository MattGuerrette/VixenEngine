#include <vix_lightmanager.h>
#include <vix_renderer_singleton.h>

namespace Vixen {

	void LightManager::Initialize()
	{

	}

	void LightManager::DeInitialize()
	{

	}

	void LightManager::RegisterLight(Light* light)
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_lights.push_back(light);
	}

	void LightManager::RenderLights()
	{
		LightManager& _manager = LightManager::instance();

		Renderer::RenderLights(_manager.m_lights);
	}
}