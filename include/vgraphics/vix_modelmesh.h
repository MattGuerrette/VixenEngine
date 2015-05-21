#ifndef VIX_MODELMESH_H
#define VIX_MODELMESH_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Vixen {

	class VIX_API ModelMesh
	{
	public:
		ModelMesh(void);

		void InitFromScene(aiScene* scene, UString fileName);

	private:
		aiMesh*  m_mesh;

	};

}

#endif