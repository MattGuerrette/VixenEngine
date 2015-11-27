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
