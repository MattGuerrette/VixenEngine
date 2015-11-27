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

#include <vix_fontutil.h>
#include <vix_debugutil.h>

namespace Vixen {

#ifdef VIX_SYS_WINDOWS
    BOOL CALLBACK EnumFamCallBack(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, DWORD FontType, LPVOID aFontCount)
    {
        int far * aiFontCount = (int far *)aFontCount;


        // Record the number of raster, TrueType, and vector
        // fonts in the font-count array.

        if (FontType & RASTER_FONTTYPE)
            aiFontCount[0]++;
        else if (FontType & TRUETYPE_FONTTYPE)
            aiFontCount[2]++;
        else
            aiFontCount[1]++;


        if (aiFontCount[0] || aiFontCount[1] || aiFontCount[2])
            return TRUE;
        else
            return FALSE;



        //UNREFERENCED_PARAMETER(lplf);
        UNREFERENCED_PARAMETER(lpntm);
    }
#endif

    void ListInstalledFontsWIN(HWND hwnd)
    {
        UINT uAlignPrev;
        int aFontCount[] = { 0, 0, 0 };
        char szCount[8];
        HRESULT hr;
        size_t * pcch;

        EnumFontFamilies(GetDC(hwnd), (LPCTSTR)NULL,
            (FONTENUMPROC)EnumFamCallBack, (LPARAM)aFontCount);

        DebugPrintF(VTEXT("Number true type: %d"), aFontCount[2]);
    }



}
