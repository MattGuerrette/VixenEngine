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

#ifndef VIX_DXMODEL_H
#define VIX_DXMODEL_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_model.h>
#include <vix_dxvertexbuffer.h>
#include <vix_dxindexbuffer.h>
#include <vix_dxinstancebuffer.h>
#include <vix_dxshader.h>
#include <vix_dxtexture.h>
#include <vix_dxcamera3d.h>
#include <vix_dxmaterial.h>

namespace Vixen {

    class VIX_API DXModel : public Model
    {
        static const int MAX_INSTANCE_PER_DRAW = 1000;
    public:
        DXModel(ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXModel();

        bool VInitFromFile(File* file)                  override;
        void VRender(float dt, float totalTime, ICamera3D* camera)                 override;
        void VSetWorld(MATRIX* matrix)					override;
        void VSetMaterial(Material* material)          override;
        void VBatchRender(MATRIX* world)                override;

        Vector3 VMin()      override;
        Vector3 VMax()      override;
        Vector3 VCenter()   override;
        Vector3 VSize()     override;

    private:
        DirectX::XMFLOAT4X4*                         m_world;
 
        ID3D11Device*                       m_device;
        ID3D11DeviceContext*                m_context;

        IVertexBuffer*                      m_vBuffer;
        IIndexBuffer*                       m_iBuffer;
        DXInstanceBuffer*                   m_instanceBuffer;
        std::vector<DXVertexPosTexNormal>   m_vertices;
        std::vector<unsigned short>         m_indices;
        DXMaterial*                         m_material;
        DXShader*                           m_vShader;
        DXShader*                           m_pShader;

        Vector3                             m_min;
        Vector3                             m_max;
        Vector3                             m_center;
        Vector3                             m_size;

        std::vector<DXInstanceData>             m_instanceData;
        //DirectX::XMFLOAT4X4                          m_instanceData[MAX_INSTANCE_PER_DRAW];
        size_t                                       m_numInstances;
        size_t                                       m_numRenderCalls;
    };
}

#endif
