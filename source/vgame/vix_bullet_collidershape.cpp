#include <vix_bullet_collidershape.h>

namespace Vixen {

	BulletColliderShape::BulletColliderShape(ColliderShapeType type)
	{
		m_type = type;
		m_shape = NULL;
	}

	btCollisionShape* BulletColliderShape::GetShape()
	{
		return m_shape;
	}

	ColliderShapeType BulletColliderShape::GetType()
	{
		return m_type;
	}
}