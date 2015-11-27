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

#ifndef VIX_LIBARCHIVE_H
#define VIX_LIBARCHIVE_H

#include <vix_platform.h>
#include <archive.h>
#include <archive_entry.h>

#ifdef VIX_SYS_LINUX
#include <unistd.h>
#endif

#define LARGE_BUFSIZE 300000

#define _FILE_OFFSET_BITS 64

VIX_API
void ARCHIVE_Extract(char* zip, char* file, BYTE* buffer);

VIX_API
void ARCHIVE_Write(const char* outname, BYTE* data, size_t len);

VIX_API
void ARCHIVE_Write(const char* outname, const char** paths);

VIX_API
BYTE*  ARCHIVE_CopyData(archive* ar);

#endif
