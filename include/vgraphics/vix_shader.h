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


#ifndef VIX_SHADER_H
#define VIX_SHADER_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_file.h>

namespace Vixen {

	enum class ShaderType
	{
		VERTEX_SHADER, /*DIRECTX & OPENGL*/
		GEOMETRY_SHADER, /*DIRECTX & OPENGL */
		TESSELATION_CONTROL_SHADER, /*OPENGL*/
		TESSELATION_EVAL_SHADER, /*OPENGL*/
		FRAGMENT_SHADER, /*OPENGL*/
        PIXEL_SHADER /*DIRECTX*/
	};

	struct ShaderInfo
	{
		ShaderType type;       /*type of shader*/
		UString    filePath;   /*path to shader*/
		UString    raw;        /*raw contents of shader*/
	};

	class VIX_API IShader
	{
	public:
		virtual ~IShader() { };

        
        virtual bool VInitFromFile(File* file) = 0;

    protected:
        virtual void VBind() = 0;
        virtual void VUnbind() = 0;
	};

}

#endif
