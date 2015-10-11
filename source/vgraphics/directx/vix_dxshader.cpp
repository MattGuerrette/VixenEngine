/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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

    bool DXShader::SetData(std::string name, const void* data, size_t size)
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

    bool DXShader::SetInt(std::string name, int data)
    {
        return SetData(name, static_cast<void*>(&data), sizeof(int));
    }

    bool DXShader::SetFloat(std::string name, float data)
    {
        return SetData(name, static_cast<void*>(&data), sizeof(float));
    }

    bool DXShader::SetFloat2(std::string name, const float data[2])
    {
        return SetData(name, static_cast<void*>(&data), sizeof(float) * 2);
    }

    bool DXShader::SetFloat2(std::string name, const DirectX::XMFLOAT2 data)
    {
        return SetData(name, &data, sizeof(float) * 2);
    }

    bool DXShader::SetFloat3(std::string name, const float data[3])
    {
        return SetData(name, static_cast<void*>(&data), sizeof(float) * 3);
    }

    bool DXShader::SetFloat3(std::string name, const DirectX::XMFLOAT3 data)
    {
        return SetData(name, &data, sizeof(float) * 3);
    }

    bool DXShader::SetFloat4(std::string name, const float data[4])
    {
        return SetData(name, static_cast<void*>(&data), sizeof(float) * 4);
    }

    bool DXShader::SetFloat4(std::string name, const DirectX::XMFLOAT4 data)
    {
        return SetData(name, &data, sizeof(float) * 4);
    }

    bool DXShader::SetMatrix4x4(std::string name, const float data[16])
    {
        return SetData(name, static_cast<void*>(&data), sizeof(float) * 16);
    }

    bool DXShader::SetMatrix4x4(std::string name, const DirectX::XMFLOAT4X4 data)
    {
        return SetData(name, &data, sizeof(float) * 16);
    }
}
