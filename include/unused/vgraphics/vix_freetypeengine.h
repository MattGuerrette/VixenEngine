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

#ifndef VIX_FREETYPEENGINE_H
#define VIX_FREETYPEENGINE_H

#include <vix_platform.h>
#include <vix_freetype.h>

namespace Vixen {

    class VIX_API FreeTypeEngine
    {
    public:
        FreeTypeEngine();

        bool Initialize();

    private:
        FT_Library  m_library;


    private:
        void DrawBitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y);
        void ShowImage();
    };

}

#endif
