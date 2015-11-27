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

#ifndef VIX_DXRESOURCELOADER_H
#define VIX_DXRESOURCELOADER_H

#include <vix_platform.h>
#include <vix_resourceloader.h>

namespace Vixen {

    class DXRenderer;

    class VIX_API DXResourceLoader : public IResourceLoader
    {
    public:
        DXResourceLoader(DXRenderer* renderer);

        ~DXResourceLoader();

        Texture*   LoadTexture(File* file)                 override;
        Shader*    LoadShader(File* file, ShaderType type) override;
        Model*     LoadModel(File* file)                   override;
        Font*      LoadFont(File* file)                    override;
		Material*  LoadMaterial(File* file)				override;

    private:
        DXRenderer* m_renderer;
    };

}

#endif
