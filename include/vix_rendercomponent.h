/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#ifndef VIX_RENDERCOMPONENT_H
#define VIX_RENDERCOMPONENT_H

#include "vix_platform.h"
#include "vix_camera3d.h"

namespace Vixen {

	class VIX_API IRenderComponent
	{
	public:
		virtual ~IRenderComponent() { };

		virtual void VRender(ICamera3D* camera) = 0;
	};

}

#endif