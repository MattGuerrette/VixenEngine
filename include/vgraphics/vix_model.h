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

#ifndef VIX_MODEL_H
#define VIX_MODEL_H

#include <vix_platform.h>
#include <vix_file.h>
#include <vix_camera3d.h>
#include <vix_material.h>
#include <vix_asset.h>

namespace Vixen {

    class VIX_API Model : public Asset
    {
    public:
		Model();

        virtual ~Model() { }

        virtual void VRender(float dt, float totalTime, ICamera3D* camera) = 0;
        virtual void VSetWorld(MATRIX* world) = 0;
        virtual void VSetMaterial(Material* material) = 0;
        virtual void VBatchRender(MATRIX* world) = 0;

        virtual Vector3 VMin() = 0;
        virtual Vector3 VMax() = 0;
        virtual Vector3 VCenter() = 0;
        virtual Vector3 VSize() = 0;
    };

}

#endif
