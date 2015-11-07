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

#ifndef VIX_ASSIMP_H
#define VIX_ASSIMP_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

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