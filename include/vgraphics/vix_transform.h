#ifndef VIX_TRANSFORM_H
#define VIX_TRANSFORM_H

#include <vix_platform.h>
#include <vix_vector3.h>

namespace Vixen {

    class VIX_API Transform
    {
    public:
        Transform();
        Transform(float posX, float posY, float posZ,
                  float rotX, float rotY, float rotZ,
                  float scaleX, float scaleY, float scaleZ);
        Transform(Vector3 position, Vector3 rotation, Vector3 scale);
    
        float X() const;
        float Y() const;
        float Z() const;
        float RotX() const;
        float RotY() const;
        float RotZ() const;
        float ScaleX() const;
        float ScaleY() const;
        float ScaleZ() const;

    private:
        Vector3 m_position;
        Vector3 m_rotation;
        Vector3 m_scale;
    };

}

#endif