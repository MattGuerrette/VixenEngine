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
        static const int MAX_INSTANCE_PER_DRAW = 10000;
    public:
        DXModel(ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXModel();

        bool VInitFromFile(File* file)                  override;
        void VRender(float dt, float totalTime, ICamera3D* camera)                 override;
		void RenderAsLight(ICamera3D* camera);
        void VSetWorld(MATRIX* matrix)					override;
        void VSetMaterial(Material* material)          override;
        void VBatchRender(MATRIX* world)                override;
		void SetInstanceCount(uint32_t instances);

        Vector3 VMin()      override;
        Vector3 VMax()      override;
        Vector3 VCenter()   override;
        Vector3 VSize()     override;

		ID3D11ShaderResourceView* InstanceView();
		DXMaterial*				  GetMaterial();

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
