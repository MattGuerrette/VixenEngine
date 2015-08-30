#ifndef VIX_DXVERTEXSHADER_H
#define VIX_DXVERTEXSHADER_H

#include <vix_platform.h>
#include <vix_dxshader.h>

namespace Vixen {

    class VIX_API DXVertexShader : public DXShader
    {
    public:
        DXVertexShader(ID3D11Device* device,
                       ID3D11DeviceContext* context);

        ~DXVertexShader();


        ID3D11VertexShader* GetShader();
        ID3D11InputLayout*  GetLayout();
       

    protected:
        bool VInitShader(File* file) override;
        void VBind() override;
        void VUnbind() override;

    private:
        ID3D11VertexShader*     m_shader;
        ID3D11InputLayout*      m_inputLayout;
    };

}

#endif