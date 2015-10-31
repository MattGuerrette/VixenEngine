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

#include <vix_dxresourceloader.h>
#include <vix_dxrenderer.h>
#include <vix_dxshader.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include <vix_dxmodel.h>
#include <vix_bmfont.h>

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
        ITexture* _texture = new DXTexture(m_renderer->Device(), m_renderer->DeviceContext());
        if (_texture->VInitFromFile(file))
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

    IModel* DXResourceLoader::LoadModel(File* file)
    {
        DXModel* _model = new DXModel(m_renderer->Device(), m_renderer->DeviceContext());
        if (_model->VInitFromFile(file))
            return _model;

        return NULL;
    }

    IFont* DXResourceLoader::LoadFont(File* file)
    {
        BMFont* _font = new BMFont;
        if (_font->VInitFromFile(file))
            return _font;

        return NULL;
    }

	IMaterial* DXResourceLoader::LoadMaterial(File* file)
	{
		DXMaterial* _material = new DXMaterial;
		if (_material->VInitFromFile(file))
			return _material;

		return NULL;
	}
}