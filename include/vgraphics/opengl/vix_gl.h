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
