#include <vix_lightmanager.h>
#include <vix_renderer_singleton.h>
#include <vix_resourcemanager.h>

namespace Vixen {

	void LightManager::Initialize()
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_lightModel = ResourceManager::OpenModel(VTEXT("icosahedron.obj"));
		_manager.m_lightModel->IncrementRefCount();
	}

	void LightManager::DeInitialize()
	{
		LightManager& _manager = LightManager::instance();
		
		ResourceManager::DecrementAssetRef(_manager.m_lightModel);
	}

	void LightManager::RegisterLight(Light* light)
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_lights.push_back(light);
	}

	void LightManager::RenderLights(ICamera3D* camera)
	{
		LightManager& _manager = LightManager::instance();

		Renderer::RenderLights(camera, _manager.m_lightModel, _manager.m_lights);
	}
}