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

#ifndef VIX_FILEUTIL_H
#define VIX_FILEUTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_debugutil.h>
#include <vix_osutil.h>

namespace Vixen {

    /*
	* Retrieves extension for file.
	* @param filePath
	* Path or Name of file
	* @param wd
	* Flag determines if user wants (.) included in extension
	*/
	VIX_API UString getFileExtension(const UString& filePath, bool wd = true);

	/*
	* Retrieves filename with extension.
	* @param filePath
	* Path of file
	* @param we
	* Flag determines if user wants fullName or baseName (no extension)
	*/
	VIX_API UString getFileName(const UString& filePath, bool we = true);

}


#endif
