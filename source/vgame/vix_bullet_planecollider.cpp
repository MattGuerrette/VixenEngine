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
