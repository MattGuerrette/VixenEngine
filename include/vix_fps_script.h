//
// Created by direc on 10/12/2022.
//

#ifndef VIX_FPS_SCRIPT_H_
#define VIX_FPS_SCRIPT_H_

#include "vix_component.h"

namespace Vixen
{
	class FpsScript : public Component
	{
	 public:
		FpsScript();

		void VOnInit() override;
		void VOnEnable() override;
		void VUpdate() override;
		void VOnDisable() override;
		void VOnDestroy() override;
	};
}

#endif //VIX_FPS_SCRIPT_H_
