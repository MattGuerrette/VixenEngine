#ifndef VIX_BULLET_COLLIDERSHAPE_H
#define VIX_BULLET_COLLIDERSHAPE_H

#include <vix_platform.h>
#include <vix_bullet.h>

namespace Vixen {

	enum class ColliderShapeType
	{
		SPHERE,
		PLANE,
		BOX
	};

	class VIX_API BulletColliderShape
	{
	public:
		BulletColliderShape(ColliderShapeType type);

		virtual ~BulletColliderShape() { }

		btCollisionShape* GetShape();

		ColliderShapeType GetType();

		virtual void VConstruct() = 0;

	protected:
		ColliderShapeType m_type;
		btCollisionShape* m_shape;
	};

}

#endif