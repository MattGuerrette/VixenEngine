/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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
