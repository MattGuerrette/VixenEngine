/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#ifndef VIX_MODEL_H
#define VIX_MODEL_H

#include "vix_platform.h"
#include "vix_file.h"
#include "vix_camera3d.h"
#include "vix_material.h"
#include "vix_asset.h"

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
