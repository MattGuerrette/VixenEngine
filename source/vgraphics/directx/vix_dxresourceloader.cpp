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
}
