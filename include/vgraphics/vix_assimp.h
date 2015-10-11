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
