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

#include <vix_dxshader.h>
#include <vix_dxtexture.h>

namespace Vixen {

    DXShader::DXShader(ID3D11Device* device, ID3D11DeviceContext* context, ShaderType type)
        : Shader()
    {
        m_type = type;
        m_device = device;
        m_context = context;
		m_shaderReflection = NULL;
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

    ShaderVariable* DXShader::FindVariable(std::string name, int size)
    {
        SVTable::iterator it = m_svTable.find(name);
        if (it == m_svTable.end())
            return NULL;

        ShaderVariable* var = &it->second;
        if (var->Size != size)
            return NULL;

        return var;
    }

    ConstantBuffer* DXShader::FindBuffer(std::string name)
    {
        CBTable::iterator it = m_cbTable.find(name);
        if (it == m_cbTable.end())
            return NULL;

        return it->second;
    }

    size_t DXShader::FindTextureBindIndex(std::string name)
    {
        TextureTable::iterator it = m_texTable.find(name);
        if (it == m_texTable.end())
            return -1;

        return it->second;
    }

    size_t DXShader::FindSampleBindIndex(std::string name)
    {
        SampleTable::iterator it = m_sampTable.find(name);
        if (it == m_sampTable.end())
            return -1;
        
        return it->second;
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
                m_texTable.insert(std::pair<std::string, size_t>(resourceDesc.Name, resourceDesc.BindPoint));
                break;

            case D3D_SIT_SAMPLER:
                m_sampTable.insert(std::pair<std::string, size_t>(resourceDesc.Name, resourceDesc.BindPoint));
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

//ReleaseCOM(m_shaderReflection);
        //ReleaseCOM(m_shaderBlob);

        return true;
    }

    void DXShader::Activate(bool update /*= true*/)
    {
        if (update)
            UpdateAllBuffers();

        VBind();
    }

    void DXShader::Deactivate()
    {
        VUnbind();
    }

    void DXShader::UpdateAllBuffers()
    {
        //iterate over all buffers and update all data
        for (size_t i = 0; i < m_cbCount; i++)
        {
            //copy local data
            m_context->UpdateSubresource(m_cbArray[i].Buffer, NULL, NULL,
                                         m_cbArray[i].LocalDataBuffer, NULL, NULL);
        }
    }

    void DXShader::UpdateBuffer(std::string name)
    {
        //Grab buffer object
        ConstantBuffer* cb = FindBuffer(name);
        if (!cb)
            return;

        //copy data into subresource
        m_context->UpdateSubresource(cb->Buffer, NULL, NULL,
                                     cb->LocalDataBuffer, NULL, NULL);
    }

    bool DXShader::VSetData(std::string name, const void* data, size_t size)
    {
        //Grab variable by name
        ShaderVariable* var = FindVariable(name, size);
        if (var == NULL)
            return false;

        //copy data into the local buffer
        memcpy(m_cbArray[var->ConstantBufferIndex].LocalDataBuffer + var->ByteOffset,
               data, size);

        return true;
    }

    bool DXShader::VSetInt(std::string name, int data)
    {
        return VSetData(name, static_cast<void*>(&data), sizeof(int));
    }

    bool DXShader::VSetFloat(std::string name, float data)
    {
        return VSetData(name, static_cast<void*>(&data), sizeof(float));
    }

    bool DXShader::VSetFloat2(std::string name, const float data[2])
    {
        return VSetData(name, static_cast<void*>(&data), sizeof(float) * 2);
    }
    
    bool DXShader::SetFloat2(std::string name, const DirectX::XMFLOAT2 data)
    {
        return VSetData(name, &data, sizeof(float) * 2);
    }
  
    bool DXShader::VSetFloat3(std::string name, const float data[3])
    {
        return VSetData(name, static_cast<void*>(&data), sizeof(float) * 3);
    }

    bool DXShader::SetFloat3(std::string name, const DirectX::XMFLOAT3 data)
    {
        return VSetData(name, &data, sizeof(float) * 3);
    }

    bool DXShader::VSetFloat4(std::string name, const float data[4])
    {
        return VSetData(name, static_cast<void*>(&data), sizeof(float) * 4);
    }

    bool DXShader::SetFloat4(std::string name, const DirectX::XMFLOAT4 data)
    {
        return VSetData(name, &data, sizeof(float) * 4);
    }

    bool DXShader::VSetMatrix4x4(std::string name, const float data[16])
    {
        return VSetData(name, static_cast<void*>(&data), sizeof(float) * 16);
    }

    bool DXShader::SetMatrix4x4(std::string name, const DirectX::XMFLOAT4X4 data)
    {
        return VSetData(name, &data, sizeof(float) * 16);
    }

	bool DXShader::VBindTexture(std::string name, Texture* texture)
	{
		bool success = true;
		success = VSetSamplerState("samLinear", ((DXTexture*)texture)->SampleState());
		success = VSetShaderResourceView(name, ((DXTexture*)texture)->ResourceView());

		return success;
	}
}