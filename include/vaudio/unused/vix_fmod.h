/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

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

#ifndef VIX_FMOD_H
#define VIX_FMOD_H

#include <fmod.hpp>
#include <fmod_errors.h>
#include <vix_errglobals.h>
#include <vix_debugutil.h>
#include <vix_stringutil.h>

namespace Vixen {

	inline
	ErrCode FMOD_CheckError(FMOD_RESULT result)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		if (result != FMOD_OK)
		{
			error = ErrCode::ERR_FAILURE;

			DebugPrintF(VTEXT("FMOD Error: %s\n%s\n"),
				FMOD_ErrorString(result),
				ErrCodeString(error));
		}

		return error;
	}
}



#endif