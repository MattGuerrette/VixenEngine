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

#ifndef VIX_DXMATERIAL_H
#define VIX_DXMATERIAL_H

#include <vix_platform.h>
#include <vix_material.h>
#include <vix_dxtexture.h>
#include <vix_dxshader.h>
#include <vix_shadervariable.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include <vix_tinyxml.h>

namespace Vixen {



    class VIX_API DXMaterial : public Material
    {
    public:
        DXMaterial();

        ~DXMaterial();

        void VBind();
        void VUnbind();

		DXVertexShader* GetVertexShader();


		bool VInitFromFile(File* file);

		UString VFilePath();

    private:
        std::map<ShaderRole,  DXShader*>		m_shaders;
		UString									m_path;

	private:
    };

}

#endif
