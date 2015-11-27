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

#ifndef VIX_SNDFILE_H
#define VIX_SNDFILE_H

//VIXEN INCLUDES
#include <vix_platform.h>

#include <sndfile.h>

#define SNDFILE_BUFFERLEN 4096

struct SNDFILE_DATA
{
	SNDFILE*  handle;
	SF_INFO   sfinfo;
	int       position;
	float     amplitude;
};

VIX_API
SNDFILE_DATA* SNDFILE_ReadFile(const char* filePath);

#endif
