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

#ifndef VIX_DIRECTX_H
#define VIX_DIRECTX_H

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <vix_debugutil.h>

struct DXVertexPosColor
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT4 color;

    DXVertexPosColor() {
        pos.x = 0.0f; pos.y = 0.0f; pos.z = 0.0f;
        color.x = 0.0f; color.y = 0.0f; color.z = 0.0f; color.w = 1.0f;
    }

    DXVertexPosColor(float _x, float _y, float _z,
                     float _r, float _g, float _b, float _a)
    {
        pos.x = _x; pos.y = _y; pos.z = _z;
        color.x = _r; color.y = _g; color.z = _b; color.w = _a;
    }
};

struct DXVertexPosTex
{
    DirectX::XMFLOAT3 pos;
    float             u;
    float             v;

    DXVertexPosTex() {
        pos.x = 0.0f; pos.y = 0.0f; pos.z = 0.0f;
        u = 0.0f; v = 0.0f;
    }

    DXVertexPosTex(float _x, float _y, float _z,
                   float _u, float _v)
    {
        pos.x = _x; pos.y = _y; pos.z = _z;
        u = _u; v = _v;
    }
};

struct DXVertexPosTexNormal
{
    DirectX::XMFLOAT3 pos;
    float             u;
    float             v;
    DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 tangent;
	DirectX::XMFLOAT3 bitangent;

    DXVertexPosTexNormal() {
        pos.x = 0.0f; pos.y = 0.0f; pos.z = 0.0f;
        u = 0.0f; v = 0.0f;
        normal.x = 0.0f; normal.y = 0.0f; normal.z = 0.0f;
		tangent.x = 0.0f; tangent.y = 0.0f; tangent.z = 0.0f;
		bitangent.x = 0.0f; bitangent.y = 0.0f; bitangent.z = 0.0f;
    }

    DXVertexPosTexNormal(float _x, float _y, float _z,
        float _u, float _v,
        float _nx, float _ny, float _nz,
		float _tx, float _ty, float _tz,
		float _btx, float _bty, float _btz)
    {
        pos.x = _x; pos.y = _y; pos.z = _z;
        u = _u; v = _v;
        normal.x = _nx; normal.y = _ny; normal.z = _nz;
		tangent.x = _tx; tangent.y = _ty; tangent.z = _tz;
		bitangent.x = _btx; bitangent.y = _bty; bitangent.z = _btz;
    }
};


struct ConstantBuffer
{
    DirectX::XMMATRIX mWorld;
    DirectX::XMMATRIX mView;
    DirectX::XMMATRIX mProjection;
};


template <typename T>
void ReleaseCOM(T* comPtr)
{
    if (comPtr)
        comPtr->Release();
}

inline void DXCheckError(HRESULT hr)
{
    LPTSTR err = NULL;
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&err, 0, NULL);
    if (err != NULL)
    {
        Vixen::DebugPrintF(VTEXT("%s"), err);

        LocalFree(err);
        err = NULL;
    }
}

#endif
