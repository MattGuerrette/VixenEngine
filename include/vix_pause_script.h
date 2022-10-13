//
// Created by direc on 10/12/2022.
//

#ifndef VIX_PAUSE_SCRIPT_H_
#define VIX_PAUSE_SCRIPT_H_

#include "vix_component.h"

namespace Vixen
{
	class PauseScript : public Component
	{
	 public:
		PauseScript();

		void VOnInit() override;
		void VOnEnable() override;
		void VUpdate() override;
		void VOnDisable() override;
		void VOnDestroy() override;
	};
}

#endif //VIX_PAUSE_SCRIPT_H_