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

#ifndef VIX_ZLIB_H
#define VIX_ZLIB_H

#include <vix_platform.h>
#include <zlib.h>
#include <zip.h>
#include <unzip.h>
#ifdef _WIN32
#define USEWIN32IOAPI
#include <iowin32.h>
#endif

#include <stdio.h>

#define ZIPBUFSIZE 8192

VIX_API
void ZLIB_Error(int error_code);

VIX_API
int ZLIB_NumFiles(const char* zipPath);

VIX_API
BYTE* ZLIB_OpenRaw(const char* zipPath, const char* file);

VIX_API
FILE* ZLIB_OpenFile(const char* zipPath, const char* file);

VIX_API
void ZLIB_FreeRaw(BYTE* raw);

VIX_API
void ZLIB_FreeFile(FILE* fp);

#endif
