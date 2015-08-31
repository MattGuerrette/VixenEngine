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

#include <vix_dxcamera3d.h>

namespace Vixen {

    DXCamera3D::DXCamera3D()
    {
        m_aspect = 0.0f;
        m_fov = 0.0f;
        m_znear = 0.0f;
        m_zfar = 1000.0f;
        m_position = DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
        m_front = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        m_standardFwd = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        m_standardRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
        m_up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        m_right = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
        m_worldUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        m_moveDir = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
        m_view = DirectX::XMMatrixIdentity();
        m_projection = DirectX::XMMatrixIdentity();
        m_yaw = 0.0f;
        m_pitch = 0.0f;
        m_speed = 10.0f;
        m_xMovement = 0.0f;
        m_zMovement = 0.0f;
    }


    DXCamera3D::DXCamera3D(C3D_TYPE type)
    {
        m_aspect = 0.0f;
        m_fov = 0.0f;
        m_znear = 0.0f;
        m_zfar = 1000.0f;
        m_position = DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
        m_front = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        m_standardFwd = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        m_standardRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
        m_up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        m_worldUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        m_right = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
        m_moveDir = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
        m_view = DirectX::XMMatrixIdentity();
        m_projection = DirectX::XMMatrixIdentity();
        m_yaw = 0.0f;
        m_pitch = 0.0f;
        m_speed = 10.0f;
        m_type = type;
        m_xMovement = 0.0f;
        m_zMovement = 0.0f;
    }

    void DXCamera3D::SetType(C3D_TYPE type)
    {
        m_type = type;
    }

    C3D_TYPE DXCamera3D::GetType()
    {
        return m_type;
    }

    void DXCamera3D::SetPerspective(float aspect, float fov, float znear, float zfar)
    {
        /*should probably check for stupid fov ranges*/
        m_aspect = aspect;
        m_fov = fov;
        m_znear = znear;
        m_zfar = zfar;
        m_projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_znear, m_zfar);
    }

    void DXCamera3D::UpdateView()
    {
        m_view = DirectX::XMMatrixLookAtLH(m_position, m_front, m_up);
    }

    void DXCamera3D::SetPosition(float x, float y, float z)
    {
        m_position = DirectX::XMVectorSet(x, y, z, 0.0f);
        UpdateView();
    }

    void DXCamera3D::Move(C3D_DIRECTION cam_dir)
    {
        DirectX::XMVECTORF32 _moveDir = { 0.0f, 0.0f, 0.0f, 0.0f };
        switch (cam_dir)
        {
            case Vixen::C3D_DIRECTION::UP:
            {
                _moveDir = { 0.0f, 1.0f, 0.0f };
                m_moveDir = _moveDir;
            }  break;
           
            case Vixen::C3D_DIRECTION::DOWN:
            {
                _moveDir = { 0.0f, -1.0f, 0.0f };
                m_moveDir = _moveDir;
            } break;
            
            case Vixen::C3D_DIRECTION::LEFT:
            {
                m_xMovement = -1;
            
            } break;
           
            case Vixen::C3D_DIRECTION::RIGHT:
            {
                m_xMovement = 1;

            } break;

            case Vixen::C3D_DIRECTION::FORWARD:
                m_zMovement = 1;
                break;
            case Vixen::C3D_DIRECTION::BACKWARD:
                m_zMovement = -1;
                break;
            default:
                break;
        }

        if (m_type == C3D_TYPE::FIRST_PERSON)
            DirectX::XMVectorSetY(m_moveDir, 0.0f);
    }


    const DirectX::XMVECTOR& DXCamera3D::Position() const
    {
        return m_position;
    }

    const DirectX::XMMATRIX& DXCamera3D::Projection() const
    {
        return m_projection;
    }

    const DirectX::XMMATRIX& DXCamera3D::View() const
    {
        return m_view;
    }

    const DirectX::XMVECTOR& DXCamera3D::Forward() const
    {
        return m_front;
    }

    void DXCamera3D::RotateY(float dt)
    {
        m_yaw = dt;
        if (m_yaw > DirectX::XM_2PI || m_yaw < -DirectX::XM_2PI)
            m_yaw = 0.0f;
    }

    void DXCamera3D::RotateX(float dt)
    {
        m_pitch = dt;
        if (this->m_pitch > DirectX::XM_PIDIV2)
            this->m_pitch = DirectX::XM_PIDIV2;
        if (this->m_pitch < -DirectX::XM_PIDIV2)
            this->m_pitch = -DirectX::XM_PIDIV2;
    }

    float DXCamera3D::Yaw()
    {
        return m_yaw;
    }

    float DXCamera3D::Pitch()
    {
        return m_pitch;
    }

    void DXCamera3D::SetSpeed(float speed)
    {
        m_speed = speed;
    }

    void DXCamera3D::Update(float dt)
    {
        float _radiansYaw = DirectX::XMConvertToRadians(this->m_yaw);
        float _radiansPitch = DirectX::XMConvertToRadians(this->m_pitch);
        m_rotation = DirectX::XMMatrixRotationRollPitchYaw(_radiansPitch, _radiansYaw, 0.0f);
        m_front = DirectX::XMVector3TransformCoord(m_standardFwd, m_rotation);
        m_right = DirectX::XMVector3TransformCoord(m_standardRight, m_rotation);
        m_standardFwd = DirectX::XMVector3Normalize(m_front);

        DirectX::XMMATRIX _tempRotY;
        _tempRotY = DirectX::XMMatrixRotationY(_radiansPitch);

        //m_right = DirectX::XMVector3TransformCoord(m_standardRight, _tempRotY);
        //m_up = DirectX::XMVector3TransformCoord(m_up, _tempRotY);*/
        m_front = DirectX::XMVector3TransformCoord(m_standardFwd, _tempRotY);
        m_right = DirectX::XMVector3Cross(m_front, m_up);
        //m_right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(this->m_front, this->m_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        //m_up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(this->m_right, this->m_front));

        DirectX::XMVECTOR moveX = DirectX::XMVectorSet(m_xMovement * dt * m_speed, 1.0f, 1.0f, 1.0f);
        DirectX::XMVECTOR moveZ = DirectX::XMVectorSet(1.0f, 1.0f, m_zMovement * dt * m_speed, 1.0f);
        
        moveX = DirectX::XMVectorMultiply(moveX, m_right);
        moveZ = DirectX::XMVectorMultiply(moveZ, m_front);
        m_position = DirectX::XMVectorAdd(m_position, moveX);
        m_position = DirectX::XMVectorAdd(m_position, moveZ);


        m_front = DirectX::XMVectorAdd(m_position, m_front);

        DebugPrintF(VTEXT("MOVEX: %.6f %.6f %.6f\n"),
            DirectX::XMVectorGetX(moveX),
            DirectX::XMVectorGetY(moveX),
            DirectX::XMVectorGetZ(moveX));
        

        UpdateView();

        m_xMovement = 0.0f;
        m_zMovement = 0.0f;
        
        //m_moveDir = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    }



}