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

#ifndef VIX_DEBUG_UTIL_H
#define VIX_DEBUG_UTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <iostream>
#include <iomanip>
#include <chrono>

#ifdef VIX_SYS_WINDOWS
#include <time.h>
#endif
#include <ctime>

#ifdef VIX_SYS_LINUX
#include <cstdarg>
#endif

#ifndef VIX_STRINGIFY
#define VIX_STRINGIFY(x) #x
#endif

#ifndef VIX_SFY_
#define VIX_SFY_(x) VIX_STRINGIFY(x)
#endif

#ifndef VIX_SFY_FUNC
#define VIX_SFY_FUNC VIX_SFY_(__FUNCTION__)
#endif

#ifndef VIX_SFY_LINE
#define VIX_SFY_LINE VIX_SFY_(__LINE__)
#endif
#ifndef VIX_SFY_FILE
#define VIX_SFY_FILE VIX_SFY_(__FILE__)
#endif

#ifndef VIX_LOG_FILE
#define VIX_LOG_FILE "FILE: " VIX_SFY_FILE
#endif
#ifndef VIX_LOG_LINE
#define VIX_LOG_LINE "LINE: " VIX_SFY_LINE
#endif

#ifndef VIX_LOG_FUNC
#define VIX_LOG_FUNC "FUNC: " __FUNCTION__
#endif

#ifndef VIX_LOG_PREFIX
#define VIX_LOG_PREFIX VIX_LOG_FILE "\n" VIX_LOG_FUNC "\n" VIX_LOG_LINE "\n"
#endif


namespace Vixen {

	inline void ConsoleWriteErr(const UString& text)
	{
#if defined(VIX_SYS_WINDOWS) && defined(UNICODE)
		std::wcerr << text << std::endl;
#else
		std::cerr << text << std::endl;
#endif
	}

	//NOTE:
	//  This is declared as an "assumed" virtual definition of the
	//  debug print function, that way we can make different version
	//  of the same print function if we so choose
	//
	//  Reason:
	//		It is impossible to pass va_list around so
	//      we must create a new function with new args if
	//      we want to have different params
	//
	inline int VDebugPrintF(const UChar* format, va_list argList)
	{
		static UChar s_buffer[VIX_BUFSIZE];
		int written = -1;

#ifdef VIX_SYS_WINDOWS
	#ifdef UNICODE
			written = _vsnwprintf_s(s_buffer, VIX_BUFSIZE, format, argList);
	#else
			written = vsnprintf_s(s_buffer, VIX_BUFSIZE, format, argList);
	#endif
#else
                written = vsnprintf(s_buffer, sizeof(s_buffer), format, argList);
#endif

		//Call Win32 API with formatted string
#ifdef VIX_SYS_WINDOWS
		OutputDebugString(s_buffer);
		ConsoleWriteErr(UString(s_buffer));
#else
		std::cerr << s_buffer << std::endl;
#endif
		return written;
	}

	//NOTE:
	//  This version of the VDebugPrintF takes an ellipses
	//  as the argList param, allowing us to specify as many
	//  parameters as we want in the buffer
	//
	inline int DebugPrintF(const UChar* format, ...)
	{
		va_list argList;
		va_start(argList, format);

		int written = VDebugPrintF(format, argList);

		va_end(argList);
		return written;
	}


	VIX_API UString DebugTimeStamp();

}

#endif
