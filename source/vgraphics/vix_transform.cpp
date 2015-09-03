/*
    The MIT License(MIT)

    Copyright(c) 2015 Matt Guerrette

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

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

    void Transform::TranslateX(float val)
    {
        m_position.x += val;
    }

    void Transform::TranslateY(float val)
    {
        m_position.y += val;
    }

    void Transform::TranslateZ(float val)
    {
        m_position.z += val;
    }

    void Transform::RotateX(float val)
    {
        m_rotation.x += val;
    }

    void Transform::RotateY(float val)
    {
        m_rotation.y += val;
    }

    void Transform::RotateZ(float val)
    {
        m_rotation.z += val;
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