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
