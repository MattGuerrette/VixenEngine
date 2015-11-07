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

#ifndef VIX_GL_H
#define VIX_GL_H

//////////////////////////////////////////////////////////////////////////
// Checks to see if glew should be supported
// *This is checked first because GLEW must be included before
// the OpenGL (GL and GLU) headers
//////////////////////////////////////////////////////////////////////////
#ifndef VIX_NO_GLEW
#define VIX_GLEW
#endif

//////////////////////////////////////////////////////////////////////////
// This file includes operating specific paths for OpenGL (GL and GLU)
// headers, which depending on operating system may have different paths
//////////////////////////////////////////////////////////////////////////
#if defined(VIX_SYS_WINDOWS)
	//Visual C++ version of gl.h using WINGDIAPI and APIENTRY but doesn't define them
	//so window.h must be included
	#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS //disable warnings for safe function versions
	#include <windows.h>
	#ifndef NOMINMAX
	#define NOMINMAX
	#endif
	#endif

        #ifdef VIX_GLEW
        #include <GL/glew.h>
        #endif
	#include <gl/gl.h>
	#include <gl/glu.h>

#elif defined(VIX_SYS_LINUX) //Linux
        #ifdef VIX_GLEW
        #include <GL/glew.h>
        #endif
	#include <GL/gl.h>
	#include <GL/glu.h>
#elif defined(VIX_SYS_MACOS) //Mac OS
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

#endif
