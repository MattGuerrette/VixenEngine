#include <vix_dxvertexshader.h>

namespace Vixen {

    DXVertexShader::DXVertexShader(ID3D11Device* device, ID3D11DeviceContext* context)
        : DXShader(device, context, ShaderType::VERTEX_SHADER)
    {
        m_shader = nullptr;
        m_inputLayout = nullptr;
    }

    DXVertexShader::~DXVertexShader()
    {
        ReleaseCOM(m_shader);
        ReleaseCOM(m_inputLayout);
    }

    bool DXVertexShader::VInitShader(File* file)
    {
        HRESULT hr = S_OK;

        BYTE* data = new BYTE[VIX_LARGE_BUFSIZE];
        file->Seek(0, FileSeek::End);
        size_t _size = file->Tell();
        file->Seek(0, FileSeek::Set);
        file->Read(data, _size); //read all of the file into memory

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // Disable optimizations to further improve shader debugging
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
  
        ID3DBlob* errorBlob = nullptr;
        hr = D3DCompile2(data, _size, nullptr, nullptr,
            nullptr, "main", "vs_4_0", dwShaderFlags, NULL, NULL, NULL, NULL,
            &m_shaderBlob, &errorBlob);
        //hr = D3DReadFileToBlob(file->FilePath().c_str(), &m_shaderBlob);
        if (FAILED(hr))
        {
            if (errorBlob)
            {
                OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
                errorBlob->Release();
            }
            return false;
        }
        if (errorBlob) errorBlob->Release();

        // Create the vertex shader
        hr = m_device->CreateVertexShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), nullptr, &m_shader);
        if (FAILED(hr))
        {
            ReleaseCOM(m_shaderBlob);
            return false;
        }

        //Reflect shader info
        ID3D11ShaderReflection* shaderReflection;
        D3DReflect(m_shaderBlob->GetBufferPointer(),
            m_shaderBlob->GetBufferSize(),
            __uuidof(ID3D11ShaderReflection),
            reinterpret_cast<void**>(&shaderReflection));

        // Get shader info
        D3D11_SHADER_DESC shaderDesc;
        shaderReflection->GetDesc(&shaderDesc);

        // Read input layout description from shader info
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
        for (unsigned int i = 0; i< shaderDesc.InputParameters; i++)
        {
            D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
            shaderReflection->GetInputParameterDesc(i, &paramDesc);

            // Fill out input element desc
            D3D11_INPUT_ELEMENT_DESC elementDesc;
            elementDesc.SemanticName = paramDesc.SemanticName;
            elementDesc.SemanticIndex = paramDesc.SemanticIndex;
            elementDesc.InputSlot = 0;
            elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            elementDesc.InstanceDataStepRate = 0;

            // Determine DXGI format
            if (paramDesc.Mask == 1)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
            }
            else if (paramDesc.Mask <= 3)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
            }
            else if (paramDesc.Mask <= 7)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            }
            else if (paramDesc.Mask <= 15)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            }

            // Save element desc
            inputLayoutDesc.push_back(elementDesc);
        }

        // Try to create Input Layout
        hr = m_device->CreateInputLayout(
            &inputLayoutDesc[0],
            inputLayoutDesc.size(),
            m_shaderBlob->GetBufferPointer(),
            m_shaderBlob->GetBufferSize(),
            &m_inputLayout);

        if (FAILED(hr))
            return false;


        return true;
    }


    void DXVertexShader::VBind()
    {
        m_context->IASetInputLayout(m_inputLayout);
        m_context->VSSetShader(m_shader, 0, 0);

        for (size_t i = 0; i < m_cbCount; i++)
        {
            m_context->VSSetConstantBuffers(m_cbArray[i].BindIndex,
                1, &m_cbArray[i].Buffer);
        }
    }

    void DXVertexShader::VUnbind()
    {
        m_context->VSSetShader(nullptr, nullptr, 0);
    }

    ID3D11VertexShader* DXVertexShader::GetShader()
    {
        return m_shader;
    }

    ID3D11InputLayout* DXVertexShader::GetLayout()
    {
        return m_inputLayout;
    }

}