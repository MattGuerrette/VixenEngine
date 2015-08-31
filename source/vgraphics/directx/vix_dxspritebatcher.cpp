/*
    The MIT License(MIT)

    Copyright(c) 2015 Matt Guerrette

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

#include <vix_dxspritebatcher.h>
#include <vix_dxtexture.h>
#include <vix_directx.h>
#include <vix_rectangle.h>
#include <array>

namespace Vixen {

    DXSpriteBatcher::DXSpriteBatcher()
    {
        m_texture = NULL;
        m_textureCount = 0;


        //populate index buffer
        for (unsigned short i = 0, j = 0; i < MAX_BATCH_SIZE; i++, j += VERTS_PER_TEX)
        {
            //each sprite is made up of 6 indices, 3 per triangle, 2 tri's per sprite
            const std::array<unsigned short, INDICES_PER_TEX> temp =
            {
                0 + j, 1 + j, 2 + j,
                2 + j, 1 + j, 3 + j
            };
            
        }
    }

    DXSpriteBatcher::~DXSpriteBatcher()
    {

    }

    void DXSpriteBatcher::Begin(BatchSortMode mode)
    {
        m_sortMode = mode;
        m_beFlag = true;
    }

    void DXSpriteBatcher::Render(ITexture* texture, BatchInfo info)
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
        const float tex_width = (float)m_texture->GetWidth();
        const float tex_height = (float)m_texture->GetHeight();
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

        /*constructor corners*/
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
       
        //TO BE IMPLEMENTED AFTER DX BUFFER CLASSES
    }


    void DXSpriteBatcher::render_textures()
    {


        /*reset for next draw call*/
        m_textureCount = 0;
        m_textures.clear();
        m_texture = NULL;
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


}