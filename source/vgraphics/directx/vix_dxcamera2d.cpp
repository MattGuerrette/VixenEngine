#include <vix_dxcamera2d.h>

namespace Vixen {

    DXCamera2D::DXCamera2D()
    {
        m_projection = DirectX::XMMatrixIdentity();
    }

  
    void DXCamera2D::SetOrthoLHOffCenter(OrthoRect rect, float zNear, float zFar)
    {
        m_rect = rect;
        m_projection = DirectX::XMMatrixOrthographicOffCenterLH(rect.left, rect.right, rect.bottom, rect.top, zNear, zFar);
    }

  

    void DXCamera2D::SetOrthoRHOffCenter(OrthoRect rect, float zNear, float zFar)
    {
        m_rect = rect;
        m_projection = DirectX::XMMatrixOrthographicOffCenterRH(rect.left, rect.right, rect.bottom, rect.top, zNear, zFar);
    }

    const DirectX::XMMATRIX& DXCamera2D::Projection()
    {
        return m_projection;
    }

}