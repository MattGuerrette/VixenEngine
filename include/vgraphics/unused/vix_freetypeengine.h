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
