//
// Created by direc on 10/12/2022.
//

#ifndef VIX_SCRIPT_H_
#define VIX_SCRIPT_H_

#include "vix_component.h"

namespace Vixen
{
	class Script : public Component
	{
	 public:
		virtual void OnInit() = 0;
		virtual void OnEnable() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDisable() = 0;
		virtual void OnDestroy() = 0;

	 protected:

	};
}

#endif //VIX_SCRIPT_H_
