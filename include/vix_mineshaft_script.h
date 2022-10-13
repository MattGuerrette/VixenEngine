//
// Created by direc on 10/12/2022.
//

#ifndef VIX_MINESHAFT_SCRIPT_H_
#define VIX_MINESHAFT_SCRIPT_H_

#include <vector>

#include "vix_component.h"

namespace Vixen
{
	class Prefab;
	class Material;
	class MineshaftScript : public Component
	{
	 public:
		MineshaftScript();

		void VOnInit() override;
		void VOnEnable() override;
		void VUpdate() override;
		void VOnDisable() override;
		void VOnDestroy() override;
	 private:
		Prefab* RailPrefab;
		Prefab* GemPrefab;
		Prefab* BrokenPrefab;
		Prefab* BufferPrefab;
		Prefab* WallPrefab;
		Prefab* WallLeftLampPrefab;
		Prefab* WallRightLampPrefab;
		Prefab* WallBothLampPrefab;
		Prefab* SpeedBoostPrefab;

		std::vector<Material*> Materials;

		float Acceleration = 0.0f;
		float MoveSpeed = 15.0f;
		float Distance = 0.0f;
		float MaxDistance = 120.0f;
		float SectionLength = 14.8;

	};
}

#endif //VIX_MINESHAFT_SCRIPT_H_
