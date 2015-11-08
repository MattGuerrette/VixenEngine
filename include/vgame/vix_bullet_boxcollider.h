#ifndef VIX_BULLET_BOXCOLLIDER_H
#define VIX_BULLET_BOXCOLLIDER_H

#include <vix_platform.h>
#include <vix_bullet.h>
#include <vix_bullet_collidershape.h>

namespace Vixen {

	class VIX_API BulletBoxCollider : public BulletColliderShape
	{
	public:
		BulletBoxCollider();

		void SetExtents(btVector3 extents);

		void VConstruct();

	private:
		btVector3   m_extents;
	};

}

#endif