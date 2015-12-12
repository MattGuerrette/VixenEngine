
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

