#ifndef VIX_DXSPRITEBATCHER_H
#define VIX_DXSPRITEBATCHER_H

#include <vix_platform.h>
#include <vix_spritebatcher.h>
#include <vix_containers.h>
#include <vix_texture.h>

namespace Vixen {


    class VIX_API DXSpriteBatcher
    {
        /*sort mode*/
        BatchSortMode          m_sortMode;

        /*number of textures rendered*/
        size_t                 m_textureCount;

        /*batch info collection*/
        std::vector<BatchInfo> m_textures;

        /*current texture*/
        ITexture*               m_texture;

        /*begin end flag*/
        bool                   m_beFlag;

    public:
        DXSpriteBatcher();

        ~DXSpriteBatcher();

        /*prepare batcher for rendering*/
        void Begin(BatchSortMode mode);

        /*render texure*/
        void Render(ITexture* texture, BatchInfo info);

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