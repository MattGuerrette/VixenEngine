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

#ifndef VIX_DXSPRITEBATCHER_H
#define VIX_DXSPRITEBATCHER_H

#include "vix_platform.h"
#include "vix_directx.h"
#include "vix_spritebatcher.h"
#include "vix_containers.h"
#include "vix_texture.h"
#include "vix_dxvertexbuffer.h"
#include "vix_dxindexbuffer.h"
#include "vix_dxvertexshader.h"
#include "vix_dxpixelshader.h"
#include "vix_dxcamera2d.h"

namespace Vixen {


    class VIX_API DXSpriteBatcher
    {
        /*sort mode*/
        BatchSortMode          m_sortMode;

        /*number of textures rendered*/
        size_t                 m_textureCount;

        /*batch info collection*/
        std::vector<BatchInfo> m_textures;

        /*vertex list*/
        std::vector<DXVertexPosTex> m_vertices;

        /*current texture*/
        Texture*              m_texture;

        /*begin end flag*/
        bool                   m_beFlag;

        /*vertex buffer*/
        DXVPTBuffer*           m_vBuffer;

        /*index buffer*/
        DXIndexBuffer*         m_iBuffer;

        DXVertexShader*        m_vShader;

        DXPixelShader*         m_pShader;

        DXCamera2D*            m_camera2D;

        ID3D11Device*          m_device;

        ID3D11DeviceContext*   m_context;
        
        ID3D11BlendState*           m_blendState;
        ID3D11DepthStencilState*    m_depthState;

    public:
        DXSpriteBatcher(ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXSpriteBatcher();

        /*prepare batcher for rendering*/
        void Begin(BatchSortMode mode);

        /*render texure*/
        void Render(Texture* texture, BatchInfo info);

        void SetVertexShader(DXVertexShader* vShader);

        void SetPixelShader(DXPixelShader* pShader);

        void SetCamera(DXCamera2D* camera);

        /*flush batched textures*/
        void End();

    private:
        /*FLUSH BUFFERED TEXTURES*/
        void flush();

        /*SORT TEXTURES BASED ON BATCH SORT MODE*/
        void sort_textures();

        /*BUILD TEXTURE FOR RENDERING*/
        void build_texture(BatchInfo info, size_t index);

        /*RENDER BATCHED TEXTURES*/
        void render_textures();

    private:
        /*STATIC CONSTANTS*/

        static const size_t MAX_BATCH_SIZE = 1048;
        static const size_t MIN_BATCH_SIZE = 128;
        static const size_t VERTS_PER_TEX = 4;
        static const size_t INDICES_PER_TEX = 6;
        static const size_t INIT_QUEUE_SIZE = 64;
        static const size_t MAX_VERT_COUNT = MAX_BATCH_SIZE * VERTS_PER_TEX;
        static const size_t MAX_INDEX_COUNT = MAX_BATCH_SIZE * INDICES_PER_TEX;
    };
}

#endif
