/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

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
