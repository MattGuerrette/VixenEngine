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

#endif
