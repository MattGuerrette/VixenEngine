#include <vix_lightmanager.h>
#include <vix_renderer_singleton.h>
#include <vix_resourcemanager.h>

namespace Vixen {

	void LightManager::Initialize()
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_pointLightModel = ResourceManager::OpenModel(VTEXT("pointlight.obj"));
		_manager.m_pointLightModel->IncrementRefCount();
		_manager.m_pointLightMaterial = ResourceManager::OpenMaterial(VTEXT("PointLight.vmt"));
		_manager.m_pointLightMaterial->IncrementRefCount();
		_manager.m_pointLightModel->VSetMaterial(_manager.m_pointLightMaterial);

		_manager.m_spotLightModel = ResourceManager::OpenModel(VTEXT("spotlight.obj"));
		_manager.m_spotLightModel->IncrementRefCount();
		_manager.m_spotLightMaterial = ResourceManager::OpenMaterial(VTEXT("SpotLight.vmt"));
		_manager.m_spotLightMaterial->IncrementRefCount();
		_manager.m_spotLightModel->VSetMaterial(_manager.m_spotLightMaterial);
	}

	void LightManager::DeInitialize()
	{
		LightManager& _manager = LightManager::instance();
		
		ResourceManager::DecrementAssetRef(_manager.m_pointLightModel);
		ResourceManager::DecrementAssetRef(_manager.m_pointLightMaterial);

		ResourceManager::DecrementAssetRef(_manager.m_spotLightModel);
		ResourceManager::DecrementAssetRef(_manager.m_spotLightMaterial);
	}

	void LightManager::RegisterPointLight(PointLight* light, MATRIX* transform)
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_pointLights.push_back(light);

		_manager.m_pointLightModel->VBatchRender(transform);
	}

	void LightManager::RegisterSpotLight(SpotLight* light, MATRIX* transform)
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_spotLights.push_back(light);

		_manager.m_spotLightModel->VBatchRender(transform);
	}

	void LightManager::RenderLights(ICamera3D* camera)
	{
		LightManager& _manager = LightManager::instance();

		Renderer::RenderLights(camera, _manager.m_pointLightModel, _manager.m_pointLights);
		Renderer::RenderLights(camera, _manager.m_spotLightModel, _manager.m_spotLights);
	}
	
	void LightManager::ClearLights()
	{
		LightManager& _manager = LightManager::instance();

		_manager.m_pointLights.clear();
		_manager.m_spotLights.clear();
	}
	
	Material* LightManager::GetPointMaterial()
	{
		return LightManager::instance().m_pointLightMaterial;
	}

	Material* LightManager::GetSpotMaterial()
	{
		return LightManager::instance().m_spotLightMaterial;
	}
}