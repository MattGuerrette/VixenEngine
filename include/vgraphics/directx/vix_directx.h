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

    DXVertexPosTexNormal() {
        pos.x = 0.0f; pos.y = 0.0f; pos.z = 0.0f;
        u = 0.0f; v = 0.0f;
        normal.x = 0.0f; normal.y = 0.0f; normal.z = 0.0f;
    }

    DXVertexPosTexNormal(float _x, float _y, float _z,
        float _u, float _v,
        float _nx, float _ny, float _nz)
    {
        pos.x = _x; pos.y = _y; pos.z = _z;
        u = _u; v = _v;
        normal.x = _nx; normal.y = _ny; normal.z = _nz;
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
