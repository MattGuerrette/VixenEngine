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

#include <vix_dxspritebatcher.h>
#include <vix_dxtexture.h>
#include <vix_directx.h>
#include <vix_rectangle.h>
#include <vix_resourcemanager.h>
#include <array>

namespace Vixen {

    DXSpriteBatcher::DXSpriteBatcher(ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_texture = NULL;
        m_textureCount = 0;
        m_device = device;
        m_context = context;

        m_vBuffer = new DXVPTBuffer(MAX_VERT_COUNT, m_device, m_context);
        m_iBuffer = new DXIndexBuffer(INDICES_PER_TEX * MAX_BATCH_SIZE, m_device, m_context);

        //populate index buffer
        for (unsigned short i = 0, j = 0; i < MAX_BATCH_SIZE; i++, j += VERTS_PER_TEX)
        {
            //each sprite is made up of 6 indices, 3 per triangle, 2 tri's per sprite
            const std::array<unsigned short, INDICES_PER_TEX> temp =
            {
                0 + j, 1 + j, 2 + j,
                2 + j, 1 + j, 3 + j
            };

            size_t offset = sizeof(unsigned short) * INDICES_PER_TEX;
            m_iBuffer->VUpdateSubData(i == 0 ? 0 : offset, sizeof(unsigned short), INDICES_PER_TEX, temp.data());
        }
    }

    DXSpriteBatcher::~DXSpriteBatcher()
    {
        ResourceManager::DecrementAssetRef(m_vShader);
		ResourceManager::DecrementAssetRef(m_pShader);

        delete m_vBuffer;
        delete m_iBuffer;
    }

    void DXSpriteBatcher::Begin(BatchSortMode mode)
    {
        m_sortMode = mode;
        m_beFlag = true;
    }

    void DXSpriteBatcher::Render(Texture* texture, BatchInfo info)
    {
        if (!texture)
            return;

        if (m_textureCount >= MAX_BATCH_SIZE || m_texture && (m_texture != texture))
        {
            /*sort textures*/
            sort_textures();

            /*flush*/
            flush();
        }

        /*add texture to collection*/
        m_textures.push_back(info);
        m_textureCount++;

        /*cache texture*/
        m_texture = (DXTexture*)texture;

        /*if immediate mode, flush*/
        if (m_sortMode == BatchSortMode::IMMEDITATE)
            flush();
    }

    void DXSpriteBatcher::End()
    {
        if (m_sortMode != BatchSortMode::IMMEDITATE) {
            /*sort textures*/
            sort_textures();

            /*flush*/
            flush();
        }

        m_beFlag = false;
    }

    void DXSpriteBatcher::sort_textures()
    {
        switch (m_sortMode)
        {
            case BatchSortMode::BACK_TO_FRONT:
            {
                /*sort back to front*/
                std::sort(m_textures.begin(), m_textures.end(), [](const BatchInfo x, const BatchInfo y)
                {
                    return x.depth > y.depth;
                });
            } break;

            case BatchSortMode::FRONT_TO_BACK:
            {
                /*sort back to front*/
                std::sort(m_textures.begin(), m_textures.end(), [](const BatchInfo x, const BatchInfo y)
                {
                    return x.depth < y.depth;
                });
            } break;

            default:
                break;
        }
    }

    void DXSpriteBatcher::build_texture(BatchInfo info, size_t index)
    {
        /*cache texture width and height*/
        const float tex_width = (float)m_texture->VGetWidth();
        const float tex_height = (float)m_texture->VGetHeight();
        const float inv_tex_width = 1.0f / tex_width;
        const float inv_tex_height = 1.0f / tex_height;

        //----------------------
        // x1 = x
        // y1 = y
        // x2 = x + width
        // y2 = y + height
        //
        //(x1,y1)-----------(x2,y1)
        // |                      |
        // |                      |
        // |                      |
        // |                      |
        // |                      |
        // |                      |
        //(x1,y2)-----------(x2,y2)


        /*store origin offset based on position*/
        const float worldOriginX = info.x + info.originX;
        const float worldOriginY = info.y + info.originY;

        /*create corner points (pre-transform)*/
        float fx = -info.originX;
        float fy = -info.originY;
        float fx2;
        float fy2;
        if (info.sW != 0 || info.sH != 0) {
            fx2 = info.sW - info.originX;
            fy2 = info.sH - info.originY;
        }
        else {
            fx2 = tex_width - info.originX;
            fy2 = tex_height - info.originY;
        }

        /*apply scale*/
        fx *= info.scaleX;
        fy *= info.scaleY;
        fx2 *= info.scaleX;
        fy2 *= info.scaleY;

        /*construct corners*/
        const float c1x = fx;
        const float c1y = fy;
        const float c2x = fx2;
        const float c2y = fy;
        const float c3x = fx;
        const float c3y = fy2;
        const float c4x = fx2;
        const float c4y = fy2;


        /*create temp vars for corner points to have rotation applied*/
        float x1;
        float y1;
        float x2;
        float y2;
        float x3;
        float y3;
        float x4;
        float y4;

        /*apply rotation*/
        if (info.rotation) {

            const float cos = DirectX::XMScalarCos(info.rotation);
            const float sin = DirectX::XMScalarSin(info.rotation);

            //To rotate a point around origin point
            //the solution follows the trigonometric function:
            //[x'] = [cos0 - sin0][x]
            //[y'] = [sin0 + cos0][y]
            //
            //So when expanded we are left with:
            //
            // x' = x * cos0 - y * sin0
            // y' = x * sin0 + y * cos0
            //

            x1 = cos * c1x - sin * c1y;
            y1 = sin * c1x + cos * c1y;
            x2 = cos * c2x - sin * c2y;
            y2 = sin * c2x + cos * c2y;
            x3 = cos * c3x - sin * c3y;
            y3 = sin * c3x + cos * c3y;
            x4 = cos * c4x - sin * c4y;
            y4 = sin * c4x + cos * c4y;
        }
        else { /*no rotation*/
            x1 = c1x;
            y1 = c1y;
            x2 = c2x;
            y2 = c2y;
            x3 = c3x;
            y3 = c3y;
            x4 = c4x;
            y4 = c4y;
        }

        /*add origin offset*/
        x1 += worldOriginX;
        y1 += worldOriginY;
        x2 += worldOriginX;
        y2 += worldOriginY;
        x3 += worldOriginX;
        y3 += worldOriginY;
        x4 += worldOriginX;
        y4 += worldOriginY;

        /*setup uv's appropriate to source rect*/
        float u;
        float v;
        float u2;
        float v2;

        Rect src_rect((int)info.sX, (int)info.sY, (int)info.sW, (int)info.sH);
        if (src_rect.HasValue()) {
            u = info.sX * inv_tex_width;
            v = info.sY * inv_tex_height;
            u2 = (info.sX + info.sW) * inv_tex_width;
            v2 = (info.sY + info.sH) * inv_tex_height;
        }
        else {
            u = 0.0f;
            v = 0.0f;
            u2 = 1.0f;
            v2 = 1.0f;
        }

        /*build vertices*/
        m_vertices.push_back(DXVertexPosTex(x1, y1, 0.0f, u, v));
        m_vertices.push_back(DXVertexPosTex(x2, y2, 0.0f, u2, v));
        m_vertices.push_back(DXVertexPosTex(x3, y3, 0.0f, u, v2));
        m_vertices.push_back(DXVertexPosTex(x4, y4, 0.0f, u2, v2));

        size_t offset = sizeof(DXVertexPosTex) * index * VERTS_PER_TEX;
        m_vBuffer->VUpdateSubData(offset, sizeof(DXVertexPosTex), m_vertices.size(), &m_vertices[0]);
    }


    void DXSpriteBatcher::render_textures()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;

        dsDesc.DepthEnable = FALSE;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
        dsDesc.StencilEnable = false;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        dsDesc.BackFace = dsDesc.FrontFace;
        ID3D11DepthStencilState* dsState;
        m_device->CreateDepthStencilState(&dsDesc, &dsState);

        m_context->OMSetDepthStencilState(dsState, 0);

        ReleaseCOM(dsState);

        m_vShader->SetMatrix4x4("projection", m_camera2D->Projection());
        m_pShader->VSetSamplerState("samLinear",  ((DXTexture*)m_texture)->SampleState());
        m_pShader->VSetShaderResourceView("txDiffuse", ((DXTexture*)m_texture)->ResourceView());

        m_vShader->Activate();
        m_pShader->Activate();
        m_vBuffer->VBind();
        m_iBuffer->VBind();

        m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_context->DrawIndexed(INDICES_PER_TEX* MAX_BATCH_SIZE, 0, 0);

        /*reset for next draw call*/
        m_textureCount = 0;
        m_textures.clear();
        m_vertices.clear();
        m_texture = NULL;

        m_context->OMSetDepthStencilState(NULL, 0);
    }

    void DXSpriteBatcher::flush()
    {
        /*if no textures, return*/
        if (m_textureCount <= 0)
            return;

        /*build all textures in batched info list*/
        for (size_t i = 0; i < m_textureCount; i++) {
            BatchInfo info = m_textures[i];

            /*build texture*/
            build_texture(info, i);
        }

        /*render texture*/
        render_textures();
    }

    void DXSpriteBatcher::SetVertexShader(DXVertexShader* vShader)
    {
        m_vShader = vShader;
    }

    void DXSpriteBatcher::SetPixelShader(DXPixelShader* pShader)
    {
        m_pShader = pShader;
    }

    void DXSpriteBatcher::SetCamera(DXCamera2D* camera)
    {
        m_camera2D = camera;
    }
}
