/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/


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
#include <vix_texture.h>

namespace Vixen {

    struct ConstantBuffer
    {
        size_t          BindIndex;
        ID3D11Buffer*   Buffer;
        BYTE*           LocalDataBuffer;
    };

    struct StructuredBuffer
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

    class VIX_API DXShader : public Shader
    {
        typedef std::unordered_map<std::string, ConstantBuffer*> CBTable;
        typedef std::unordered_map<std::string, StructuredBuffer*> SBTable;
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
        bool VSetData(std::string name, const void* data, size_t size);
        bool VSetInt(std::string name, int data);
        bool VSetFloat(std::string name, float data);
        bool VSetFloat2(std::string name, const float data[2]);
        bool VSetFloat3(std::string name, const float data[3]);
        bool VSetFloat4(std::string name, const float data[4]);
        bool VSetMatrix4x4(std::string name, const float data[16]);

		bool SetFloat2(std::string name, const DirectX::XMFLOAT2 data);
		bool SetFloat3(std::string name, const DirectX::XMFLOAT3 data);
		bool SetFloat4(std::string name, const DirectX::XMFLOAT4 data);
		bool SetMatrix4x4(std::string name, const DirectX::XMFLOAT4X4 data);

		bool VBindTexture(std::string name, Texture* texture);
        bool VUnbindTexture(std::string name, Texture* texture);

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
        size_t                  m_sbCount;
        ConstantBuffer*         m_cbArray;
        CBTable                 m_cbTable;
        SVTable                 m_svTable;
        SBTable                 m_sbTable;
        TextureTable            m_texTable;
        SampleTable             m_sampTable;
        ID3D11Device*           m_device;
        ID3D11DeviceContext*    m_context;
        ID3DBlob*               m_shaderBlob;
        ID3D11ShaderReflection* m_shaderReflection;


    };

}

#endif
