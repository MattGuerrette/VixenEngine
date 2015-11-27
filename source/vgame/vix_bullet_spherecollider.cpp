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
