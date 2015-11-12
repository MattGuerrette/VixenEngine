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

#include <vix_dxmodel.h>
#include <vix_assimp.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include <vix_tinyxml.h>
#include <vix_pathmanager.h>
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
		m_material = nullptr;

		m_world = new XMFLOAT4X4;

        m_numInstances = 0;
        m_numRenderCalls = 0;
    }

    DXModel::~DXModel()
    {
        delete m_vBuffer;
        delete m_iBuffer;
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

        return true;
    }

    void DXModel::VSetMaterial(Material* material)
    {
        m_material = (DXMaterial*)material;
    }

	void DXModel::VRender(float dt, float totalTime, ICamera3D* camera)
	{
		if (m_numInstances <= 0)
			return;

		m_context->RSSetViewports(1, &((DXCamera3D*)camera)->GetViewport());

		m_material->GetVertexShader()->SetMatrix4x4("projection", ((DXCamera3D*)camera)->Projection());
		m_material->GetVertexShader()->SetMatrix4x4("view", ((DXCamera3D*)camera)->View());
		m_material->GetVertexShader()->VSetData("transforms", &m_instanceData[0] , (sizeof(float) * 16) * MAX_INSTANCE_PER_DRAW);
		m_material->VBind();

        m_vBuffer->VBind();
        m_iBuffer->VBind();
        m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_context->DrawIndexedInstanced(m_indices.size(), m_numInstances, 0, 0, 0);

        m_material->VUnbind();

        ///m_instanceData.clear();
        m_numInstances = 0;
        m_numRenderCalls = 0;
    }

    void DXModel::VSetWorld(MATRIX* world)
    {
		XMStoreFloat4x4(m_world, XMMatrixTranspose(*world));
        //m_instanceData.push_back(*m_world);
    }

    void DXModel::VBatchRender(MATRIX* world)
    {
        XMFLOAT4X4 _transform;

        XMStoreFloat4x4(&_transform, XMMatrixTranspose(*world));
        m_instanceData[m_numInstances] = _transform;

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