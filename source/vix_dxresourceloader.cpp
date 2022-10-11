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

#include <vix_dxresourceloader.h>
#include <vix_dxrenderer.h>
#include <vix_dxshader.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include <vix_dxmodel.h>
#include <vix_bmfont.h>
#include "vix_filemanager.h"

namespace Vixen {

    DXResourceLoader::DXResourceLoader(DXRenderer* renderer)
    {
        m_renderer = renderer;
    }

    DXResourceLoader::~DXResourceLoader()
    {

    }

    Texture* DXResourceLoader::LoadTexture(File* file)
    {
        DXTexture* _texture = new DXTexture(m_renderer->Device(), m_renderer->DeviceContext());
        if (_texture->VInitFromFile(file))
            return _texture;

        return NULL;
    }

    Shader* DXResourceLoader::LoadShader(File* file, ShaderType type)
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

    Model* DXResourceLoader::LoadModel(File* file)
    {
        DXModel* _model = new DXModel(m_renderer->Device(), m_renderer->DeviceContext());
        if (_model->VInitFromFile(file))
            return _model;

        return NULL;
    }

    Font* DXResourceLoader::LoadFont(File* file)
    {
        BMFont* _font = new BMFont;
        if (_font->VInitFromFile(file))
            return _font;

        return NULL;
    }

	Material* DXResourceLoader::LoadMaterial(File* file)
	{
		DXMaterial* _material = new DXMaterial;

		if (_material->VInitFromFile(file))
			return _material;

		return NULL;
	}

}
