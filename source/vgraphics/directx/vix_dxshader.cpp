#include <vix_dxshader.h>

namespace Vixen {

    DXShader::DXShader(ID3D11Device* device, ID3D11DeviceContext* context, ShaderType type)
    {
        m_type = type;
        m_device = device;
        m_context = context;
    }

    DXShader::~DXShader()
    {
        // Handle constant buffers and local data buffers
        for (unsigned int i = 0; i < m_cbCount; i++)
        {
            m_cbArray[i].Buffer->Release();
            delete[] m_cbArray[i].LocalDataBuffer;
        }
        delete[] m_cbArray;
        m_cbCount = 0;

        // Clean up tables
        m_svTable.clear();
        m_cbTable.clear();
        m_sampTable.clear();
        m_texTable.clear();
    }

    bool DXShader::VInitFromFile(File* file)
    {
        
        if (!this->VInitShader(file))
            return false;
            
        if (!m_shaderReflection)
        {
            //Reflect shader info
            D3DReflect(m_shaderBlob->GetBufferPointer(),
                m_shaderBlob->GetBufferSize(),
                __uuidof(ID3D11ShaderReflection),
                reinterpret_cast<void**>(&m_shaderReflection));
        }

        //Get description of the shader
        D3D11_SHADER_DESC shaderDesc;
        m_shaderReflection->GetDesc(&shaderDesc);

        //Create array of constant buffers
        m_cbCount = shaderDesc.ConstantBuffers;
        m_cbArray = new ConstantBuffer[m_cbCount];

        //Handle bound resources (shaders or samples)
        size_t resourceCnt = shaderDesc.BoundResources;
        for (size_t i = 0; i < resourceCnt; i++)
        {
            //Get the resource description
            D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
            m_shaderReflection->GetResourceBindingDesc(i, &resourceDesc);

            //Check what type
            switch (resourceDesc.Type)
            {
            case D3D_SIT_TEXTURE:
                break;

            case D3D_SIT_SAMPLER:
                break;
            }
        }

        //Loop over all constant buffers
        for (size_t i = 0; i < m_cbCount; i++)
        {
            //Get this buffer
            ID3D11ShaderReflectionConstantBuffer* cb =
                m_shaderReflection->GetConstantBufferByIndex(i);

            //Get description of buffer
            D3D11_SHADER_BUFFER_DESC bufferDesc;
            cb->GetDesc(&bufferDesc);

            //Get the description of the resource binding
            //so we know how its bound to shader
            D3D11_SHADER_INPUT_BIND_DESC bindDesc;
            m_shaderReflection->GetResourceBindingDescByName(bufferDesc.Name, &bindDesc);

            //set up buffer and put its pointer into the table
            m_cbArray[i].BindIndex = bindDesc.BindPoint;
            m_cbTable.insert(std::pair<std::string, ConstantBuffer*>(bufferDesc.Name, &m_cbArray[i]));
        
            //Create this constant buffer
            D3D11_BUFFER_DESC _newBufferDesc;
            _newBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            _newBufferDesc.ByteWidth = bufferDesc.Size;
            _newBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            _newBufferDesc.CPUAccessFlags = 0;
            _newBufferDesc.MiscFlags = 0;
            _newBufferDesc.StructureByteStride = 0;
            m_device->CreateBuffer(&_newBufferDesc, 0, &m_cbArray[i].Buffer);
        
            //setup the data buffer for the cb
            m_cbArray[i].LocalDataBuffer = new BYTE[bufferDesc.Size];
            ZeroMemory(m_cbArray[i].LocalDataBuffer, bufferDesc.Size);

            //Iterate over all variables in this buffer
            for (size_t v = 0; v < bufferDesc.Variables; v++)
            {
                //Get this variables
                ID3D11ShaderReflectionVariable* var =
                    cb->GetVariableByIndex(v);

                //Get variable description
                D3D11_SHADER_VARIABLE_DESC varDesc;
                var->GetDesc(&varDesc);

                //Create the variable struct
                ShaderVariable variable;
                variable.ConstantBufferIndex = i;
                variable.ByteOffset = varDesc.StartOffset;
                variable.Size = varDesc.Size;
                
                //Get a string representation
                std::string varName = varDesc.Name;

                //Add variable to table
                m_svTable.insert(std::pair<std::string, ShaderVariable>(varName, variable));
            }
        }

        ReleaseCOM(m_shaderReflection);
        ReleaseCOM(m_shaderBlob);

        return true;
    }


  

}