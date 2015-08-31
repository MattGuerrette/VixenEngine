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

#ifndef VIX_DXCAMERA3D_H
#define VIX_DXCAMERA3D_H

#include <vix_platform.h>
#include <vix_directx.h>

namespace Vixen {

    enum class C3D_DIRECTION
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FORWARD,
        BACKWARD
    };

    enum class C3D_TYPE
    {
        FREEFORM,
        FIRST_PERSON,
    };


    class VIX_API DXCamera3D
    {
        static const int YAW = -90;
        static const int PITCH = 0;
    public:
        DXCamera3D();

        DXCamera3D(C3D_TYPE type);

        /*Get Position*/
        const DirectX::XMVECTOR& Position() const;
        
        /*Get Projection Matrix*/
        const DirectX::XMMATRIX& Projection() const;

        const DirectX::XMVECTOR& Forward() const;

        /*Get View Matrix*/
        const DirectX::XMMATRIX& View() const;

        /*Set Perspective Projection*/
        void SetPerspective(float aspect, float fov, float znear, float zfar);

        /*Update view lens*/
        void UpdateView();

        /*Set Speed*/
        void SetSpeed(float speed);

        /*Set Position*/
        void SetPosition(float x, float y, float z);

        /*Get Type*/
        C3D_TYPE GetType();

        /*Set Camera Type*/
        void SetType(C3D_TYPE type);

        /*Move Camera*/
        void Move(C3D_DIRECTION cam_dir);

        /*Rotate Y*/
        void RotateY(float dt);

        /*Rotate X*/
        void RotateX(float dt);

        /*Update Camera*/
        void Update(float dt);

        float Yaw();

        float Pitch();

    private:
        DirectX::XMMATRIX	m_projection;
        DirectX::XMMATRIX	m_view;
        DirectX::XMMATRIX   m_rotation;

        DirectX::XMVECTOR       m_position;
        DirectX::XMVECTOR       m_front;
        DirectX::XMVECTOR       m_up;
        DirectX::XMVECTOR       m_right;
        DirectX::XMVECTOR       m_worldUp;
        DirectX::XMVECTOR       m_moveDir;
        DirectX::XMVECTOR       m_standardFwd;
        DirectX::XMVECTOR       m_standardRight;

        C3D_TYPE m_type;

        float   m_yaw;
        float   m_pitch;
        float   m_aspect;
        float   m_fov;
        float   m_znear;
        float   m_zfar;
        float   m_speed;

        float   m_xMovement;
        float   m_zMovement;
    };

}

#endif
