#include <vix_dxresourceloader.h>
#include <vix_dxrenderer.h>
#include <vix_dxshader.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include <vix_filemanager.h>

namespace Vixen {

    DXResourceLoader::DXResourceLoader(DXRenderer* renderer)
    {
        m_renderer = renderer;
    }

    DXResourceLoader::~DXResourceLoader()
    {

    }

    ITexture* DXResourceLoader::LoadTexture(File* file)
    {
        DXTexture* _texture = new DXTexture(m_renderer->Device());
        if (_texture->InitFromFile(file))
            return _texture;

        return NULL;
    }

    IShader* DXResourceLoader::LoadShader(File* file, ShaderType type)
    {
        DXShader* _shader = NULL;

        if (type == ShaderType::VERTEX_SHADER)
            _shader = new DXVertexShader(m_renderer->Device(),
                m_renderer->DeviceContext());
        else if (type == ShaderType::PIXEL_SHADER)
            _shader = new DXPixelShader(m_renderer->Device(),
                m_renderer->DeviceContext());

        if (_shader->VInitFromFile(file))
            return _shader;

        return NULL;
    }

}