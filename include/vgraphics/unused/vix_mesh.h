#ifndef VIX_MESH_H
#define VIX_MESH_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_assimp.h>
#include <vix_glbuffers.h>
#include <vix_vertex_defs.h>
#include <vix_glcamera3d.h>

namespace Vixen {


	class Model;

	struct MeshInfo
	{
		size_t				NumVertices;
		size_t				NumIndices;
		std::vector<Vec3>	Vertices;
	};

	class VIX_API Mesh
	{
	public:
		Mesh(Model* parent, MeshInfo* info);

		~Mesh();

		void AddVertex(float x, float y, float z,
				       float nx, float ny, float nz,
					   float u, float v,
					   float tx, float ty, float tz);
		void AddFace(unsigned short index1,
					 unsigned short index2,
					 unsigned short index3);
		void Init();
		void Render(GLCamera3D* camera); 

		/*GETTERS*/

		const MeshInfo* const  GetInfo() const;

	private:
		void applyTransform(GLCamera3D* camera);

	private:
		Model*                                m_parent;
		MeshInfo*                             m_info;
		VBuffers::PNTVBuffer*				  m_vBuffer;
		GLIndexBuffer*                        m_iBuffer;
		std::vector<PositionNormalTexture>    m_vertices;
		std::vector<unsigned short>           m_indices;
		size_t                                m_numVertices;
		size_t                                m_numIndices;
	};

}

#endif