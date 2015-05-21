#include <vix_assimp.h>

void
FindMeshCenter(aiMesh* mesh, aiVector3D& out, aiVector3D& min, aiVector3D& max)
{
	MeshBounds(mesh->mVertices, mesh->mNumVertices, min, max);
	out = (min + max) * 0.5f;
}