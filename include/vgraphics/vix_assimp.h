#ifndef VIX_ASSIMP_H
#define VIX_ASSIMP_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

//NEED TO UNDEFINE WINDOWS MIN/MAX MACROS
//WHAT A PAIN IN THE ASS....

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

//template <typename T>
//inline void ArrayBounds(const T* in, size_t sz, T& min, T& max)
//{
//	min = in[0];
//	max = in[0];
//	for(size_t i = 0; i < sz; i++) {
//		min = std::min(in[i], min);
//		max = std::max(in[i], max);
//	}
//}

inline void MeshBounds(const aiVector3D* in, size_t size, aiVector3D& min, aiVector3D& max)
{
	min = in[0];
	max = in[0];
	for(size_t i = 0; i < size; i++) {
		min.x = std::min(in[i].x, min.x);
		min.y = std::min(in[i].y, min.y);
		min.z = std::min(in[i].z, min.z);

		max.x = std::max(in[i].x, max.x);
		max.y = std::max(in[i].y, max.y);
		max.z = std::max(in[i].z, max.z);
	}
}

void
FindMeshCenter(aiMesh* mesh, aiVector3D& out, aiVector3D& min, aiVector3D& max);

#endif