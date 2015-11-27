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

#include <vix_sndfile.h>

SNDFILE_DATA*
SNDFILE_ReadFile(const char* filePath)
{
	SNDFILE_DATA* data = new SNDFILE_DATA;
	data->handle = sf_open(filePath, SFM_READ, &data->sfinfo);
	data->amplitude = 1.0f;
	data->position = 0;

	return data;
}
