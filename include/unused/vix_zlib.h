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
