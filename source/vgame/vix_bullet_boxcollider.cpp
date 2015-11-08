#include <vix_bullet_boxcollider.h>

namespace Vixen {

	BulletBoxCollider::BulletBoxCollider()
		: BulletColliderShape(ColliderShapeType::BOX)
	{
		
	}

	void BulletBoxCollider::SetExtents(btVector3 extents)
	{
		m_extents = extents;
	}

	void BulletBoxCollider::VConstruct()
	{
		m_shape = new btBoxShape(m_extents / 2.0f);
	}

}