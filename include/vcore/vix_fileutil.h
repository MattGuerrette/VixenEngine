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
