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

#ifndef VIX_PLATFORM
#define VIX_PLATFORM

//NOTE:
//
//	Define platform macros, used for precompiler blocks when
//	writing platform specific routines
//

#ifdef _WIN32
	//Windows platform
	#define VIX_SYS_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#ifndef NOMINMAX
	#define NOMINMAX
	#endif
#elif defined(__linux__)
	//linux platform
	#define VIX_SYS_LINUX
#elif defined(__APPLE__)
	#define VIX_SYS_MACOS
#else
	#error System is not supported by Vixen
#endif


//////////////////////////////////////////////////////////////////////////
// Define header to create portable import / export macros
//////////////////////////////////////////////////////////////////////////

#ifndef VIX_IMPORT
	#ifdef VIX_SYS_WINDOWS
		#define VIX_IMPORT __declspec(dllimport)
	#else
		#define VIX_IMPORT __attribute__ ((__visibility__("default")))
	#endif
#endif

#ifndef VIX_EXPORT
#ifdef VIX_SYS_WINDOWS
		#define VIX_EXPORT __declspec(dllexport)
	#else
		#define VIX_EXPORT __attribute__ ((__visibility__("default")))
	#endif
#endif

#if !defined(VIX_STATIC)
	#ifdef VIX_SYS_WINDOWS
		#if defined (VIX_NONCLIENT_BUILD)
			//define dllexport and dllimport macros
			#ifndef VIX_API
			#define VIX_API __declspec(dllexport)
			#endif
		#else
			#ifndef VIX_API
			#define VIX_API __declspec(dllimport)
			#endif
		#endif

		//Visual c++ compiler warning C4251 disable
		#ifdef _MSC_VER
		#pragma warning(disable : 4251)
		#endif

	#else //Linux and MAC OS X
		#if __GNUC__ >= 4
			//GCC 4 has unique keywords for showing/hiding symbols
			//the same keyword is used for both import and export
			#define VIX_API __attribute__ ((__visibility__("default")))
			#define VIX_API __attribute__ ((__visibility__("default")))
		#else
			#define VIX_API
			#define VIX_API
		#endif
	#endif
#else
	//static build doesn't need import/export macros
	#define VIX_API
	#define VIX_API
#endif

/*BYTE define for non Windows platforms*/
#ifndef _WIN32
typedef unsigned char BYTE;
#endif

#ifndef VIX_BUFSIZE
#define VIX_BUFSIZE 1024
#endif

#ifndef VIX_LARGE_BUFSIZE
#define VIX_LARGE_BUFSIZE 10240
#endif

#endif
