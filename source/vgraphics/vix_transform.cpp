#include <vix_transform.h>

namespace Vixen {

    Transform::Transform()
    {
        m_position = Vector3(0.0f, 0.0f, 0.0f);
        m_rotation = Vector3(0.0f, 0.0f, 0.0f);
        m_scale = Vector3(1.0f, 1.0f, 1.0f);
    }

    Transform::Transform(float posX, float posY, float posZ,
                         float rotX, float rotY, float rotZ,
                         float scaleX, float scaleY, float scaleZ)
    {
        m_position = Vector3(posX, posY, posZ);
        m_rotation = Vector3(rotX, rotY, rotZ);
        m_scale = Vector3(scaleX, scaleY, scaleZ);
    }

    Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
    {
        m_position = position;
        m_rotation = rotation;
        m_scale = scale;
    }

    float Transform::X() const
    {
        return m_position.x;
    }

    float Transform::Y() const
    {
        return m_position.y;
    }

    float Transform::Z() const
    {
        return m_position.z;
    }

    float Transform::RotX() const
    {
        return m_rotation.x;
    }

    float Transform::RotY() const
    {
        return m_rotation.y;
    }

    float Transform::RotZ() const
    {
        return m_rotation.z;
    }

    float Transform::ScaleX() const
    {
        return m_scale.x;
    }
    
    float Transform::ScaleY() const
    {
        return m_scale.y;
    }

    float Transform::ScaleZ() const
    {
        return m_scale.z;
    }
}