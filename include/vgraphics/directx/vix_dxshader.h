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


/*
*   CREDIT:
*   Adapted from SimpleShader class written by Chris Cascioli
*
*/

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

        virtual bool VSetShaderResourceView(std::string name, ID3D11ShaderResourceView* rv) = 0;
        virtual bool VSetSamplerState(std::string name, ID3D11SamplerState* ss) = 0;

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
