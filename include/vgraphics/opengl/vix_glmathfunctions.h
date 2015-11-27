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

#ifndef VIX_GLMATHFUNCTIONS_H
#define VIX_GLMATHFUNCTIONS_H

#include <vix_platform.h>
#include <vix_math.h>
#include <vix_vector3.h>

namespace Vixen {

    class VIX_API GLMathFunctions
    {
    public:
        static MATRIX MatrixRotation(Vector3 rotation);
        static MATRIX MatrixTranslation(Vector3 position);
        static MATRIX MatrixRotationX(float rotX);
        static MATRIX MatrixRotationY(float rotY);
        static MATRIX MatrixRotationZ(float rotZ);
        static MATRIX MatrixScaling(Vector3 scale);
        static MATRIX MatrixInverse(MATRIX matrix);

        static Vector3 TransformVector(Vector3 v, MATRIX matrix);
        static Vector3 TransformVectorRotationScale(Vector3 v, MATRIX matrix);
    };

}

#endif
