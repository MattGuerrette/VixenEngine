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


#include <vix_dxpixelshader.h>

namespace Vixen {

    DXPixelShader::DXPixelShader(ID3D11Device* device, ID3D11DeviceContext* context)
        : DXShader(device, context, ShaderType::PIXEL_SHADER)
    {
        m_shader = nullptr;
    }

    DXPixelShader::~DXPixelShader()
    {
        ReleaseCOM(m_shader);
    }

    bool DXPixelShader::VInitShader(File* file)
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
            nullptr, "main", "ps_5_0", NULL, NULL, NULL, NULL, NULL,
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
        hr = m_device->CreatePixelShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), nullptr, &m_shader);
        if (FAILED(hr))
        {
            ReleaseCOM(m_shaderBlob);
            return false;
        }

        return true;
    }

    void DXPixelShader::VBind()
    {
        m_context->PSSetShader(m_shader, nullptr, 0);

        // Set the constant buffers
        for (size_t i = 0; i < m_cbCount; i++)
        {
            m_context->PSSetConstantBuffers(
                m_cbArray[i].BindIndex,
                1,
                &m_cbArray[i].Buffer);
        }
    }

    void DXPixelShader::VUnbind()
    {
        m_context->PSSetShader(0, 0, 0);
    }

    bool DXPixelShader::VSetShaderResourceView(std::string name, ID3D11ShaderResourceView* rv)
    {
        //find variable
        size_t index = FindTextureBindIndex(name);
        if (index == -1)
            return false;

        //set resource view
        m_context->PSSetShaderResources(index, 1, &rv);

        return true;
    }

    bool DXPixelShader::VSetSamplerState(std::string name, ID3D11SamplerState* ss)
    {
        //find variable
        size_t index = FindSampleBindIndex(name);
        if (index == -1)
            return false;

        //set sample state
        m_context->PSSetSamplers(index, 1, &ss);

        return true;
    }

    ID3D11PixelShader* DXPixelShader::GetShader()
    {
        return m_shader;
    }

}