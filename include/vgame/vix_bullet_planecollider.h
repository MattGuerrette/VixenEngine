#ifndef VIX_BULLET_PLANECOLLIDER_H
#define VIX_BULLET_PLANECOLLIDER_H

#include <vix_platform.h>
#include <vix_bullet.h>
#include <vix_bullet_collidershape.h>

namespace Vixen {

	class VIX_API BulletPlaneCollider : public BulletColliderShape
	{
	public:
		BulletPlaneCollider();

		void SetPlaneNormal(btVector3 normal);
		void SetPlaneContant(btScalar val);

		void VConstruct();

	private:
		btVector3 m_planeNormal;
		btScalar  m_planeConstant;
	};
}

#endif
