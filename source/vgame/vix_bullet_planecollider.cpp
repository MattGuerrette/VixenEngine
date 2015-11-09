#include <vix_bullet_planecollider.h>

namespace Vixen {

	BulletPlaneCollider::BulletPlaneCollider()
		: BulletColliderShape(ColliderShapeType::PLANE)
	{
		m_planeNormal = btVector3(0.0f, 1.0f, 0.0f);
		m_planeConstant = 1.0f;
	}

	void BulletPlaneCollider::SetPlaneNormal(btVector3 normal)
	{
		m_planeNormal = normal;
	}

	void BulletPlaneCollider::SetPlaneContant(btScalar val)
	{
		m_planeConstant = val;
	}

	void BulletPlaneCollider::VConstruct()
	{
		m_shape = new btStaticPlaneShape(m_planeNormal, m_planeConstant);
	}


}