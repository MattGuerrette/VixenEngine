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

#ifndef VIX_FONTUTIL_H
#define VIX_FONTUTIL_H

#include <vix_platform.h>

#ifdef VIX_SYS_WINDOWS
#include <Windows.h>
#endif

namespace Vixen {


    VIX_API
    void ListInstalledFontsWIN(HWND hwnd);


}

#endif
