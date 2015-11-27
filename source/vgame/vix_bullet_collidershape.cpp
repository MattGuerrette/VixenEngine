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
