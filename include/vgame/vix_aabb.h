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

#ifndef VIX_AABB_H
#define VIX_AABB_H

#include <vix_platform.h>
#include <vix_transform.h>
#include <vix_component.h>

namespace Vixen {

    class VIX_API AABB : public Component
    {
    public:
        AABB(Vector3 centroid, Vector3 halfSize);

        ~AABB();


        Vector3 Min() const;
        Vector3 Max() const;
        Vector3 Centroid() const;
        Vector3 Size() const;


        void VUpdate() override;

        static bool CheckCollision(AABB* a, AABB* b);

    private:
        void UpdateTransformed();

    private:
        Vector3 m_position;
        Vector3 m_centroid;
        Vector3 m_size;
        Vector3 m_min;
        Vector3 m_max;

        Transform* m_parent;
    };

}

#endif
