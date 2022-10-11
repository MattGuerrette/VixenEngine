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

#ifndef VIX_AABB_H
#define VIX_AABB_H

#include "vix_platform.h"
#include "vix_transform.h"
#include "vix_component.h"

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
