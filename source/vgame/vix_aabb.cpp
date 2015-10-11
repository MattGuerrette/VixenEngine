/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vix_aabb.h>

namespace Vixen {

    AABB::AABB(Vector3 centroid, Vector3 halfSize)
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
