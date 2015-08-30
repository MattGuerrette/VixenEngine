#ifndef VIX_PIXELSHADER_H
#define VIX_PIXELSHADER_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_dxshader.h>

namespace Vixen {

    class VIX_API DXPixelShader : public DXShader
    {
    public:
        DXPixelShader(ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXPixelShader();

        ID3D11PixelShader* GetShader();


    protected:
        bool VInitShader(File* file) override;
        void VBind() override;
        void VUnbind() override;

    private:
        ID3D11PixelShader* m_shader;

    };

}

#endif
