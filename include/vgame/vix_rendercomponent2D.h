#ifndef VIX_RENDERCOMPONENT2D_H
#define VIX_RENDERCOMPONENT2D_H

#include <vix_platform.h>
#include <vix_camera2d.h>

namespace Vixen {

	class VIX_API IRenderComponent2D
	{
	public:
		virtual ~IRenderComponent2D() { };

		virtual void VRender(ICamera2D* camera, Viewport v) = 0;
	};

}

#endif
