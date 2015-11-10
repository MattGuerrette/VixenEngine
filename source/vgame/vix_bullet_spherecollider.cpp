#include <vix_bullet_spherecollider.h>

namespace Vixen {

	BulletSphereCollider::BulletSphereCollider()
		: BulletColliderShape(ColliderShapeType::SPHERE)
	{
		m_radius = 1.0f;
	}

	void BulletSphereCollider::SetRadius(btScalar radius)
	{
		m_radius = radius;
	}

	void BulletSphereCollider::VConstruct()
	{
		m_shape = new btSphereShape(m_radius);
	}

}