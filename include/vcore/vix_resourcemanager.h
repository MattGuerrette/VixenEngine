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

#ifndef VIX_RESOURCEMANAGER_H
#define VIX_RESOURCEMANAGER_H

#include <vix_platform.h>
#include <vix_filemanager.h>
#include <vix_resourceloader.h>
#include <vix_texture.h>
#include <vix_shader.h>

namespace Vixen {

    

    /**
    *   ResourceType enum class
    *
    *   Defines the different available resource types
    *   usable by Vixen Game Engine
    */
    enum class ResourceType
    {
        Texture,
        Model,
        Font,
        Shader
    };

    /**
    *   ResourceManager class
    *
    *   Defines the resource manager object that is used to load
    *   game content into the Vixen Game Engine at runtime.
    */
    class VIX_API ResourceManager : public Singleton<ResourceManager>
    {
    public:
        ~ResourceManager();

        static void     AttachResourceLoader(IResourceLoader* loader);
        static ITexture* OpenTexture(UString filePath);
        static IShader*  OpenShader(UString filePath, ShaderType type);
       
        //static void     OpenResource(UString fileName, ResourceType type);
        //static File*    AccessResource(UString fileName, ResourceType type);

    private:
        IResourceLoader* m_resourceLoader;
    };




}

#endif
