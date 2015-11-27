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

#ifndef VIX_ERR_GLOBALS_H
#define VIX_ERR_GLOBALS_H

#include <vix_platform.h>
#include <vix_stringutil.h>

enum class ErrCode
{
	ERR_FAILURE,
	ERR_SUCCESS,
	ERR_NULL_PATH,
	ERR_FILE_NOT_FOUND,
	ERR_SDL_INIT_FAIL,
	ERR_SDL_CREATE_FAIL,
	ERR_IMAGE_LOAD_FAIL,
	ERR_XML_READ_FAIL,
	ERR_XML_WRITE_FAIL,
	ERR_GLEW_INIT_FAIL,
};

inline UString ErrCodeString(ErrCode error)
{
	UString errorMsg;

	switch (error)
	{
	case ErrCode::ERR_FAILURE:
		errorMsg = VTEXT("ERR_FAILURE");
		break;
	case ErrCode::ERR_SUCCESS:
		errorMsg = VTEXT("ERR_SUCCESS");
		break;
	case ErrCode::ERR_NULL_PATH:
		errorMsg = VTEXT("ERR_NULL_PATH");
		break;
	case ErrCode::ERR_FILE_NOT_FOUND:
		errorMsg = VTEXT("ERR_FILE_NOT_FOUND");
		break;
	case ErrCode::ERR_SDL_CREATE_FAIL:
		errorMsg = VTEXT("ERR_SDL_CREATE_FAIL");
		break;
	case ErrCode::ERR_SDL_INIT_FAIL:
		errorMsg = VTEXT("ERR_SDL_INIT_FAIL");
		break;
	case ErrCode::ERR_IMAGE_LOAD_FAIL:
		errorMsg = VTEXT("ERR_IMAGE_LOAD_FAIL");
		break;

	case ErrCode::ERR_XML_READ_FAIL:
		errorMsg = VTEXT("ERR_XML_READ_FAIL");
		break;

	case ErrCode::ERR_XML_WRITE_FAIL:
		errorMsg = VTEXT("ERR_XML_WRITE_FAIL");
		break;

	case ErrCode::ERR_GLEW_INIT_FAIL:
		errorMsg = VTEXT("ERR_GLEW_INIT_FAIL");
		break;

	default:
		errorMsg = VTEXT("UNKNOWN ERROR");
		break;
	}

	return errorMsg;
}

inline bool CheckError(ErrCode error)
{
	return error != ErrCode::ERR_SUCCESS;
}


#endif
