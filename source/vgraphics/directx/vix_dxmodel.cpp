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
    {
        m_device = device;
        m_context = context;
        m_material = new DXMaterial;
        m_vBuffer = nullptr;
        m_iBuffer = nullptr;

		m_world = new XMFLOAT4X4;

        m_numInstances = 0;
        m_numRenderCalls = 0;
    }

    DXModel::~DXModel()
    {
        delete m_material;
        delete m_vBuffer;
        delete m_iBuffer;
    }

    bool DXModel::VInitFromFile(File* file)
    {
        using namespace tinyxml2;

        //File is actually an XML file
        //we should now open for reading
        XMLDOC document;
        XMLError err = document.LoadFile(file->Handle());
        UString errString;
        if (XMLErrCheck(err, errString))
        {
            DebugPrintF(VTEXT("MDL File failed to load\n"));
            return false;
        }

        //Now we want to parse the value of the model
        const XMLElement* modelElement = document.FirstChildElement("model");
        const XMLElement* fileElement = modelElement->FirstChildElement("file");
        const XMLElement* vShaderElement = modelElement->FirstChildElement("vertex-shader");
        const XMLElement* pShaderElement = modelElement->FirstChildElement("pixel-shader");

        const char* modelfile = fileElement->Attribute("val");
        const char* vShaderFile = vShaderElement->Attribute("val");
        const char* pShaderFile = pShaderElement->Attribute("val");

        //set material shaders
        m_material->VSetShader(IMaterial::ShaderRole::Vertex,
            ResourceManager::OpenShader(UStringFromCharArray(vShaderFile), ShaderType::VERTEX_SHADER));
        m_material->VSetShader(IMaterial::ShaderRole::Pixel,
            ResourceManager::OpenShader(UStringFromCharArray(pShaderFile), ShaderType::PIXEL_SHADER));
        m_vShader = m_material->GetShader(IMaterial::ShaderRole::Vertex);
        m_pShader = m_material->GetShader(IMaterial::ShaderRole::Pixel);

        UString _modelPath = PathManager::AssetPath() + VTEXT("Models/Data/") + UStringFromCharArray(modelfile);
        _modelPath = os_path(_modelPath);
        Assimp::Importer _importer;
        std::string _path = UStringToStd(_modelPath);
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
        m_iBuffer->VSetData(&m_indices[0]);

        //create material
        if (scene->HasMaterials())
        {
            aiMaterial* mat = scene->mMaterials[scene->mNumMaterials - 1];

            aiString name;
            aiGetMaterialString(mat, AI_MATKEY_NAME, &name);
            //grab ambient color
            aiColor4D ambientColor;
            aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
            m_material->VSetAmbientColor(Color(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a));

            //grab diffuse color
            aiColor4D diffuseColor;
            aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
            m_material->VSetDiffuseColor(Color(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a));

            //grab specular color
            aiColor4D specularColor;
            aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &specularColor);
            m_material->VSetSpecularColor(Color(specularColor.r, specularColor.g, specularColor.b, specularColor.a));

            //grab specular shininess
            float specularWeight;
            aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &specularWeight);
            m_material->VSetSpecularWeight(specularWeight);

            //Set diffuse matertial texture
            aiString diffuse;
            aiGetMaterialTexture(mat, aiTextureType_DIFFUSE, 0, &diffuse);

            if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                ITexture* diffuseTexture = ResourceManager::OpenTexture(UStringFromCharArray(diffuse.data));
                if (diffuseTexture)
                    m_material->VSetTexture(IMaterial::TextureRole::Diffuse, diffuseTexture);
            }

        }

        return true;
    }

    void DXModel::VSetMaterial(IMaterial* material)
    {
        m_material = (DXMaterial*)material;
        m_vShader = m_material->GetShader(IMaterial::ShaderRole::Vertex);
        m_pShader = m_material->GetShader(IMaterial::ShaderRole::Pixel);
    }

    void DXModel::VRender(float dt, ICamera3D* camera)
    {
        if (!m_vShader || !m_pShader || m_numInstances <= 0)
            return;

       

        m_vShader->SetMatrix4x4("projection", ((DXCamera3D*)camera)->Projection());
        m_vShader->SetMatrix4x4("view", ((DXCamera3D*)camera)->View());

		if (m_material->GetTexture(IMaterial::TextureRole::Diffuse)) {
            
			m_pShader->VSetSamplerState("samLinear", m_material->GetTexture(IMaterial::TextureRole::Diffuse)->SampleState());
			m_pShader->VSetShaderResourceView("txDiffuse", m_material->GetTexture(IMaterial::TextureRole::Diffuse)->ResourceView());
		}
		else {
			m_pShader->VSetSamplerState("samLinear", NULL);
			m_pShader->VSetShaderResourceView("txDiffuse", NULL);
		}

       /* int i = 0;
        while (i <= m_numRenderCalls)
        {
            int offset = i * MAX_INSTANCE_PER_DRAW;*/
            m_vShader->SetData("transforms", &m_instanceData[0] , (sizeof(float) * 16) * MAX_INSTANCE_PER_DRAW);

            m_vShader->Activate();
            m_pShader->Activate();
            m_vBuffer->VBind();
            m_iBuffer->VBind();
            m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            m_context->DrawIndexedInstanced(m_indices.size(), m_numInstances, 0, 0, 0);

         /*   i++;
        }*/

        


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