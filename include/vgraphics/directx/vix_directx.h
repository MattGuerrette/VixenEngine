#ifndef VIX_DIRECTX_H
#define VIX_DIRECTX_H

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <vix_debugutil.h>

struct VertexPos
{
    DirectX::XMFLOAT3 pos;
    //DirectX::XMFLOAT4 color;
};

struct VertexTex
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 uv;
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
