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
