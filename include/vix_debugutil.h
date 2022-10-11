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

#ifndef VIX_DEBUG_UTIL_H
#define VIX_DEBUG_UTIL_H

#include <vix_platform.h>
#include "vix_stringutil.h"
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
		std::wcerr << text;
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
		ConsoleWriteErr(UString(s_buffer));
		OutputDebugString(s_buffer);
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
