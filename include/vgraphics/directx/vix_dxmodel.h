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

#ifndef VIX_DXMODEL_H
#define VIX_DXMODEL_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_model.h>
#include <vix_dxvertexbuffer.h>
#include <vix_dxindexbuffer.h>
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
        std::vector<DXVertexPosTexNormal>   m_vertices;
        std::vector<unsigned short>         m_indices;
        DXMaterial*                         m_material;
        DXShader*                           m_vShader;
        DXShader*                           m_pShader;

        Vector3                             m_min;
        Vector3                             m_max;
        Vector3                             m_center;
        Vector3                             m_size;

        //std::vector<DirectX::XMFLOAT4X4>             m_instanceData;
        DirectX::XMFLOAT4X4                          m_instanceData[MAX_INSTANCE_PER_DRAW];
        size_t                                       m_numInstances;
        size_t                                       m_numRenderCalls;
    };
}

#endif
