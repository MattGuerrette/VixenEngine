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

<<<<<<< HEAD
        ITexture*   LoadTexture(File* file)                 override;
        IShader*    LoadShader(File* file, ShaderType type) override;
        IModel*     LoadModel(File* file)                   override;
        IFont*      LoadFont(File* file)                    override;

=======
        Texture*   LoadTexture(File* file)                 override;
        Shader*    LoadShader(File* file, ShaderType type) override;
        Model*     LoadModel(File* file)                   override;
        Font*      LoadFont(File* file)                    override;
		Material*  LoadMaterial(File* file)				override;
       
>>>>>>> 7e4502b797e001a298b2a224c9fc4b4dcc75a61d
    private:
        DXRenderer* m_renderer;
    };

}

#endif
