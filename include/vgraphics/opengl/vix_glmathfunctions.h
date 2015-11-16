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
