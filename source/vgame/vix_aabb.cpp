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

#include <vix_aabb.h>

namespace Vixen {

    AABB::AABB(Vector3 centroid, Vector3 halfSize) : Component(Type::UNUSED)
    {

    }

    AABB::~AABB()
    {

    }

    Vector3 AABB::Max() const
    {
        return m_max;
    }

    Vector3 AABB::Min() const
    {
        return m_min;
    }

    Vector3 AABB::Centroid() const
    {
        return m_centroid;
    }

    Vector3 AABB::Size() const
    {
        return m_size;
    }

    void AABB::UpdateTransformed()
    {
        //We need to recalculate the centroid and size and min and max,
        //based on the transformed model. To do this, we need the vertices of the model again

    }

    void AABB::VUpdate()
    {

    }

    bool AABB::CheckCollision(AABB* a, AABB* b)
    {
        bool colliding = true;

        Vector3 aMin = a->Min();
        Vector3 aMax = a->Max();
        Vector3 bMin = b->Min();
        Vector3 bMax = b->Max();

        if (aMax.x < bMin.x || aMin.x > bMax.y)
            colliding = false;
        else if (aMax.y < bMin.y || aMin.y > bMax.y)
            colliding = false;
        else if (aMax.z < bMin.z || aMin.z > bMax.z)
            colliding = false;

        return colliding;
    }
}
