#ifndef VIX_DXCAMERA2D_H
#define VIX_DXCAMERA2D_H

#include <vix_platform.h>
#include <vix_directx.h>

namespace Vixen {

    enum class OrthoType
    {
        ORTHO_LH,
        ORTHO_LH_OFFCENTER,
        ORTHO_RH,
        ORTHO_RH_OFFCENTER
    };

    struct OrthoRect
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    class VIX_API DXCamera2D
    {
    public:
        DXCamera2D();
        
        void SetOrthoLHOffCenter(OrthoRect rect, float zNear, float zFar);
        void SetOrthoRHOffCenter(OrthoRect rect, float zNear, float zFar);

        const DirectX::XMMATRIX& Projection();

    private:
        OrthoType          m_type;
        DirectX::XMMATRIX  m_projection;
        OrthoRect          m_rect;
        float              m_zNear;
        float              m_zFar;
    };

}

#endif
