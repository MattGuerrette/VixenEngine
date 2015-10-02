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
