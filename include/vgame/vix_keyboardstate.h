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

#ifndef VIX_KEYBOARDSTATE_H
#define VIX_KEYBOARDSTATE_H

#include <vix_platform.h>
#include <vix_input.h>

namespace Vixen {

	class VIX_API IKeyboardState
	{
	public:
		virtual ~IKeyboardState() { };

		virtual bool VKeyPress(IKEY key) = 0;
		virtual bool VSingleKeyPress(IKEY key) = 0;
		virtual bool VKeyRelease(IKEY key) = 0;
	};

}

#endif
