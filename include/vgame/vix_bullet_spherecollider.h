#ifndef VIX_BULLET_SPHERECOLLIDER_H
#define VIX_BULLET_SPHERECOLLIDER_H

#include <vix_platform.h>
#include <vix_bullet.h>
#include <vix_bullet_collidershape.h>

namespace Vixen {

	class VIX_API BulletSphereCollider : public BulletColliderShape
	{
	public:
		BulletSphereCollider();

		void SetRadius(btScalar radius);

		void VConstruct();

	private:
		btScalar m_radius;
	};

}

#endif