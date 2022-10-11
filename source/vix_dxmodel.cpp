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

#include <vix_dxmodel.h>
#include <vix_assimp.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include "vix_tinyxml.h"
#include "vix_pathmanager.h"
#include <vix_resourcemanager.h>
#include <vix_mathfunctions.h>

using namespace DirectX;

namespace Vixen {

    DXModel::DXModel(ID3D11Device* device, ID3D11DeviceContext* context)
        : Model()
    {
        m_device = device;
        m_context = context;
        m_vBuffer = nullptr;
        m_iBuffer = nullptr;

        m_instanceBuffer = nullptr;
		m_material = nullptr;

		m_world = new XMFLOAT4X4;

        m_numInstances = 0;
        m_numRenderCalls = 0;
    }

    DXModel::~DXModel()
    {
        delete m_vBuffer;
        delete m_iBuffer;
        delete m_instanceBuffer;
    }

    bool DXModel::VInitFromFile(File* file)
    {
        using namespace tinyxml2;

        Assimp::Importer _importer;
		std::string _path = UStringToStd(file->FilePath());
        const aiScene* scene = _importer.ReadFile(_path.c_str(), aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_GenNormals |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType |
            aiProcess_GenUVCoords |
            aiProcess_TransformUVCoords |
            aiProcess_FlipUVs);
        if (!scene)
        {
            const UChar* message = UStringFromCharArray(_importer.GetErrorString()).c_str();
            DebugPrintF(VTEXT("ASSIMP READ ERROR: %s\n"), message);
            return false;
        }

        //Read mesh information into
        //a DXMesh object

        aiMesh* mesh = scene->mMeshes[0];

        aiVector3D min, max, center;
        FindMeshCenter(mesh, center, min, max);
        m_min = Vector3(min.x, min.y, min.z);
        m_max = Vector3(max.x, max.y, max.z);
        aiVector3D size = max - min;
        m_size = Vector3(size.x, size.y, size.z);
        m_center = Vector3(center.x, center.y, center.z);

        size_t numVertices = mesh->mNumVertices;

		for (size_t i = 0; i < numVertices; i++)
		{
			aiVector3D vertex = mesh->mVertices[i];

			DXVertexPosTexNormal _vert;
			_vert.pos.x = vertex.x;
			_vert.pos.y = vertex.y;
			_vert.pos.z = vertex.z;

			if (mesh->HasNormals()) {
				aiVector3D normal;
				normal = mesh->mNormals[i];
				_vert.normal.x = normal.x;
				_vert.normal.y = normal.y;
				_vert.normal.z = normal.z;
			}

			if (mesh->HasTangentsAndBitangents()) {
				aiVector3D tangent;
				tangent = mesh->mTangents[i];
				aiVector3D bitangent;
				bitangent = mesh->mBitangents[i];

				_vert.tangent.x = tangent.x;
				_vert.tangent.y = tangent.y;
				_vert.tangent.z = tangent.z;

				_vert.bitangent.x = bitangent.x;
				_vert.bitangent.y = bitangent.y;
				_vert.bitangent.z = bitangent.z;
			}

			if (mesh->HasTextureCoords(0)) {
				aiVector3D uvs = mesh->mTextureCoords[0][i];
				_vert.u = uvs.x;
				_vert.v = uvs.y;
			}


            m_vertices.push_back(_vert);
        }

        size_t numFaces = mesh->mNumFaces;
        for (size_t i = 0; i < numFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            m_indices.push_back(face.mIndices[0]);
            m_indices.push_back(face.mIndices[1]);
            m_indices.push_back(face.mIndices[2]);
        }

        m_vBuffer = new DXVPTNBuffer(m_vertices.size(), m_device, m_context);
        m_vBuffer->VUpdateSubData(0, sizeof(DXVertexPosTexNormal), m_vertices.size(), m_vertices.data());

        m_iBuffer = new DXIndexBuffer(m_indices.size(), m_device, m_context);
        m_iBuffer->VUpdateSubData(0, sizeof(unsigned short), m_indices.size(), &m_indices[0]);

        m_instanceBuffer = new DXInstanceBuffer(1000, m_device, m_context);
        return true;
    }

    void DXModel::VSetMaterial(Material* material)
    {
        m_material = (DXMaterial*)material;
    }

	DXMaterial* DXModel::GetMaterial()
	{
		return m_material;
	}

	void DXModel::VRender(float dt, float totalTime, ICamera3D* camera)
	{

		if (m_numInstances <= 0 || m_instanceData.size() <= 0)
			return;
 
		m_context->RSSetViewports(1, &((DXCamera3D*)camera)->GetViewport());

        m_instanceBuffer->VUpdateSubData(0, sizeof(DXInstanceData), m_instanceData.size(), &m_instanceData[0]);

		m_material->GetVertexShader()->SetMatrix4x4("projection", ((DXCamera3D*)camera)->Projection());
		m_material->GetVertexShader()->SetMatrix4x4("view", ((DXCamera3D*)camera)->View());
        m_material->GetVertexShader()->VSetShaderResourceView("InstanceBuffer", m_instanceBuffer->GetSRV());
        
		m_material->VBind();

        m_vBuffer->VBind();
        m_iBuffer->VBind();
        m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_context->DrawIndexedInstanced(m_indices.size(), m_numInstances, 0, 0, 0);

        m_material->VUnbind();

        m_instanceData.clear();
        m_numInstances = 0;
        m_numRenderCalls = 0;
    }

	void DXModel::RenderAsLight(ICamera3D* camera)
	{
		if (m_numInstances <= 0)
			return;

		m_context->RSSetViewports(1, &((DXCamera3D*)camera)->GetViewport());

		m_instanceBuffer->VUpdateSubData(0, sizeof(DXInstanceData), m_instanceData.size(), &m_instanceData[0]);

		m_vBuffer->VBind();
		m_iBuffer->VBind();
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_context->DrawIndexedInstanced(m_indices.size(), m_numInstances, 0, 0, 0);

		m_instanceData.clear();
		m_numInstances = 0;
		m_numRenderCalls = 0;
	}

	ID3D11ShaderResourceView* DXModel::InstanceView()
	{
		return m_instanceBuffer->GetSRV();
	}

    void DXModel::VSetWorld(MATRIX* world)
    {
		XMStoreFloat4x4(m_world, XMMatrixTranspose(*world));
    }

	void DXModel::SetInstanceCount(uint32_t instances)
	{
		m_numInstances = instances;
	}

    void DXModel::VBatchRender(MATRIX* world)
    {
        DXInstanceData data;
        XMStoreFloat4x4(&data.world, XMMatrixTranspose(*world));
       
        m_instanceData.push_back(data);

        m_numInstances++;
        if (m_numInstances > MAX_INSTANCE_PER_DRAW)
            m_numRenderCalls++;
    }


    Vector3 DXModel::VMin()
    {
        return m_min;
    }

    Vector3 DXModel::VMax()
    {
        return m_max;
    }

    Vector3 DXModel::VCenter()
    {
        return m_center;
    }

    Vector3 DXModel::VSize()
    {
        return m_size;
    }
}
