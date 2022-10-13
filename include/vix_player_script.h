//
// Created by direc on 10/13/2022.
//

#ifndef VIX_PLAYER_SCRIPT_H_
#define VIX_PLAYER_SCRIPT_H_

#include "vix_component.h"

namespace Vixen
{
	class PlayerScript : public Component
	{
	 public:
		PlayerScript();

		void VOnInit() override;
		void VOnEnable() override;
		void VUpdate() override;
		void VOnDisable() override;
		void VOnDestroy() override;

	 private:
		bool Jumping;
		int Position;
		float StartX;
		float TargetX;
		float JumpCount;
		float MoveSpeed;
	};
}

#endif //VIX_PLAYER_SCRIPT_H_
