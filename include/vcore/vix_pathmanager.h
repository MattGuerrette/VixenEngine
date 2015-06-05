#ifndef VIX_PATHMANAGER_H
#define VIX_PATHMANAGER_H

#include <vix_platform.h>
#include <vix_osutil.h>
#include <json/json.h>

namespace Vixen
{
    class VIX_API PathManager
    {
        static const char*  FONT_LOC_KEY;
        static const char*  MEDIA_LOC_KEY;
        static const char*  TEXTURES_LOC_KEY;
    public:
        PathManager();

    private:
    };
}

#endif
