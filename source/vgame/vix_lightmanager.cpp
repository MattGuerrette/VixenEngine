#include <vix_lightmanager.h>
#include <vix_renderer_singleton.h>
#include <vix_resourcemanager.h>

namespace Vixen {

	void LightManager::Initialize()
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_lightModel = ResourceManager::OpenModel(VTEXT("icosahedron.obj"));
		_manager.m_lightMaterial = ResourceManager::OpenMaterial(VTEXT("Light.vmt"));
		_manager.m_lightMaterial->IncrementRefCount();
		_manager.m_lightModel->VSetMaterial(_manager.m_lightMaterial);
		_manager.m_lightModel->IncrementRefCount();
	}

	void LightManager::DeInitialize()
	{
		LightManager& _manager = LightManager::instance();
		
		ResourceManager::DecrementAssetRef(_manager.m_lightModel);
		ResourceManager::DecrementAssetRef(_manager.m_lightMaterial);
	}

	void LightManager::RegisterLight(Light* light, MATRIX* transform)
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_lights.push_back(light);

		_manager.m_lightModel->VBatchRender(transform);
	}

	void LightManager::RenderLights(ICamera3D* camera)
	{
		LightManager& _manager = LightManager::instance();

		Renderer::RenderLights(camera, _manager.m_lightModel, _manager.m_lights);
	}
	
	void LightManager::ClearLights()
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_lights.clear();
	}
}