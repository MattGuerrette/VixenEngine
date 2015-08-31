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

#include <vix_dxmodel.h>
#include <vix_assimp.h>

namespace Vixen {

    DXModel::DXModel(ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_device = device;
        m_context = context;
        m_vBuffer = nullptr;
        m_iBuffer = nullptr;
    }

    DXModel::~DXModel()
    {
        delete m_vBuffer;
        delete m_iBuffer;
    }

    bool DXModel::VInitFromFile(File* file)
    {

        Assimp::Importer _importer;
        std::string _path = UStringToStd(file->FilePath());
        const aiScene* scene = _importer.ReadFile(_path.c_str(),  aiProcess_CalcTangentSpace |
                                                                  aiProcess_Triangulate |
                                                                  aiProcess_JoinIdenticalVertices |
                                                                  aiProcess_SortByPType |
                                                                  aiProcess_GenUVCoords);
        if (!scene)
        {
            const UChar* message = UStringFromCharArray(_importer.GetErrorString()).c_str();
            DebugPrintF(VTEXT("ASSIMP READ ERROR: %s\n"), message);
            return false;
        }

        size_t numMeshes = scene->mNumMeshes;
        for (size_t i = 0; i < numMeshes; i++)
        {
            //Read mesh information into
            //a DXMesh object
            aiMesh* mesh = scene->mMeshes[i];

            size_t numVertices = mesh->mNumVertices;
            
            for (size_t i = 0; i < numVertices; i++)
            {
                aiVector3D vertex = mesh->mVertices[i];

                DXVertexPosColor _vert;
                _vert.pos.x = vertex.x;
                _vert.pos.y = vertex.y;
                _vert.pos.z = vertex.z;
                if (i % 2 == 0)
                    _vert.color = DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
                else
                    _vert.color = DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);

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

        }
        m_vBuffer = new DXVPCBuffer(m_vertices.size(), m_device, m_context);
        m_vBuffer->VSetData(&m_vertices[0]);

        m_iBuffer = new DXIndexBuffer(m_indices.size(), m_device, m_context);
        m_iBuffer->VSetData(&m_indices[0]);

        return true;
    }

    void DXModel::VRender()
    {
        m_vBuffer->VBind();
        m_iBuffer->VBind();

        m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_context->DrawIndexed(m_indices.size(), 0, 0);

       
    }

}