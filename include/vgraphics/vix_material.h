/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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

#ifndef VIX_MATERIAL_H
#define VIX_MATERIAL_H

#include <vix_platform.h>
#include <vix_containers.h>
#include <vix_texture.h>
#include <vix_shader.h>
#include <vix_color.h>

namespace Vixen {

    class VIX_API IMaterial
    {
    public:
        enum class TextureRole
        {
            Diffuse,
            Ambient,
            SpecularColor,
            SpecularHighlight,
            Alpha,
            Bump,
            Displacement,
            Decal
        };

        enum class ShaderRole
        {
            Vertex,
            Pixel
        };


        virtual ~IMaterial() { };

        virtual void VBind() = 0;
        virtual void VUnbind() = 0;

        virtual ITexture* VGetTexture(TextureRole role) = 0;
        virtual IShader*  VGetShader(ShaderRole role) = 0;

        virtual void VSetAmbientColor(Color color) = 0;
        virtual void VSetDiffuseColor(Color color) = 0;
        virtual void VSetSpecularColor(Color color) = 0;
        virtual void VSetSpecularWeight(float weight) = 0;
        virtual void VSetAlphaTransparency(float transparency) = 0;
        virtual void VSetTexture(TextureRole role, ITexture* texture) = 0;
        virtual void VSetShader(ShaderRole role, IShader* shader) = 0;

    };

}

#endif