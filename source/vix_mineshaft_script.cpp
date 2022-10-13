//
// Created by direc on 10/12/2022.
//

#include "vix_mineshaft_script.h"
#include "vix_prefabmanager.h"
#include "vix_material.h"
#include "vix_lightmanager.h"

namespace Vixen
{
	MineshaftScript::MineshaftScript()
		: Component(Component::Type::MINESHAFT_SCRIPT)
	{

	}

	void MineshaftScript::VOnInit()
	{
		RailPrefab = PrefabManager::Load("rail.pfb");
		RailPrefab->IncRefCount();
		GemPrefab = PrefabManager::Load("GemRail.pfb");
		GemPrefab->IncRefCount();
		BrokenPrefab = PrefabManager::Load("BrokenRail.pfb");
		BrokenPrefab->IncRefCount();
		BufferPrefab = PrefabManager::Load("Buffer.pfb");
		BufferPrefab->IncRefCount();
		WallPrefab = PrefabManager::Load("mineSection.pfb");
		WallPrefab->IncRefCount();
		WallLeftLampPrefab = PrefabManager::Load("mineSectionLeftLamp.pfb");
		WallLeftLampPrefab->IncRefCount();
		WallRightLampPrefab = PrefabManager::Load("mineSectionRightLamp.pfb");
		WallRightLampPrefab->IncRefCount();
		WallBothLampPrefab = PrefabManager::Load("mineSectionBothLamp.pfb");
		WallBothLampPrefab->IncRefCount();
		SpeedBoostPrefab = PrefabManager::Load("SpeedBoostRail.pfb");
		SpeedBoostPrefab->IncRefCount();

		auto* rail = GemPrefab->CreateObject();
		Materials.push_back(rail->GetComponent<ModelComponent>()->GetMaterial());
		Materials.push_back(rail->GetChild(0)->GetComponent<ModelComponent>()->GetMaterial());
		rail->Delete();

		auto* wall = WallLeftLampPrefab->CreateObject();
		Materials.push_back(wall->GetChild(2)->GetComponent<ModelComponent>()->GetMaterial());
		Materials.push_back(wall->GetChild(0)->GetComponent<ModelComponent>()->GetMaterial());
		Materials.push_back(wall->GetChild(1)->GetComponent<ModelComponent>()->GetMaterial());
		Materials.push_back(wall->GetChild(0)->GetChild(0)->GetComponent<ModelComponent>()->GetMaterial());
		wall->Delete();

		auto* hazard = BrokenPrefab->CreateObject();
		Materials.push_back(hazard->GetComponent<ModelComponent>()->GetMaterial());
		hazard->Delete();

		Materials.push_back(LightManager::GetPointMaterial());
		Materials.push_back(LightManager::GetSpotMaterial());

		auto* buffer = BufferPrefab->CreateObject();
		Materials.push_back(buffer->GetChild(0)->GetComponent<ModelComponent>()->GetMaterial());
		buffer->Delete();

	}

	void MineshaftScript::VOnEnable()
	{

	}

	void MineshaftScript::VUpdate()
	{

	}

	void MineshaftScript::VOnDisable()
	{

	}

	void MineshaftScript::VOnDestroy()
	{
		RailPrefab->DecRefCount();
		GemPrefab->DecRefCount();
		BrokenPrefab->DecRefCount();
		WallPrefab->DecRefCount();
		WallLeftLampPrefab->DecRefCount();
		WallRightLampPrefab->DecRefCount();
		WallBothLampPrefab->DecRefCount();
		SpeedBoostPrefab->DecRefCount();
		BufferPrefab->DecRefCount();
	}
}