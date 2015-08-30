#ifndef VIX_DXSHADER_H
#define VIX_DXSHADER_H

#include <vix_platform.h>
#include <vix_shader.h>
#include <vix_directx.h>
#include <vix_containers.h>

namespace Vixen {

    struct ConstantBuffer
    {
        size_t          BindIndex;
        ID3D11Buffer*   Buffer;
        BYTE*           LocalDataBuffer;
    };

    struct ShaderVariable
    {
        size_t ByteOffset;
        size_t Size;
        size_t ConstantBufferIndex;
    };

    class VIX_API DXShader : public IShader
    {
        typedef std::unordered_map<std::string, ConstantBuffer*> CBTable;
        typedef std::unordered_map<std::string, ShaderVariable>  SVTable;
        typedef std::unordered_map<std::string, size_t> TextureTable;
        typedef std::unordered_map<std::string, size_t> SampleTable;
    public:
        DXShader(ID3D11Device* device,
                 ID3D11DeviceContext* context,
                 ShaderType type);

        virtual ~DXShader();

        bool VInitFromFile(File* file) override;


        //Update Buffer Data
        void Activate(bool update = true);
        void Deactivate();
        void UpdateAllBuffers();
        void UpdateBuffer(std::string name);

        //Set Shader Data
        bool SetData(std::string name, const void* data, size_t size);
        bool SetInt(std::string name, int data);
        bool SetFloat(std::string name, float data);
        bool SetFloat2(std::string name, const float data[2]);
        bool SetFloat2(std::string name, const DirectX::XMFLOAT2 data);
        bool SetFloat3(std::string name, const float data[3]);
        bool SetFloat3(std::string name, const DirectX::XMFLOAT3 data);
        bool SetFloat4(std::string name, const float data[4]);
        bool SetFloat4(std::string name, const DirectX::XMFLOAT4 data);
        bool SetMatrix4x4(std::string name, const float data[16]);
        bool SetMatrix4x4(std::string name, const DirectX::XMFLOAT4X4 data);

    protected:
        virtual bool VInitShader(File* file) = 0;

        ShaderVariable* FindVariable(std::string name, int size);
        ConstantBuffer* FindBuffer(std::string name);
        size_t          FindTextureBindIndex(std::string name);
        size_t          FindSampleBindIndex(std::string name);


    protected:
        ShaderType              m_type;
        size_t                  m_cbCount;
        ConstantBuffer*         m_cbArray;
        CBTable                 m_cbTable;
        SVTable                 m_svTable;
        TextureTable            m_texTable;
        SampleTable             m_sampTable;
        ID3D11Device*           m_device;
        ID3D11DeviceContext*    m_context;
        ID3DBlob*               m_shaderBlob;
        ID3D11ShaderReflection* m_shaderReflection;

        
    };

}

#endif
