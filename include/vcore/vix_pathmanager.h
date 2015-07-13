#ifndef VIX_PATHMANAGER_H
#define VIX_PATHMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_osutil.h>

namespace Vixen
{
    class VIX_API PathManager : public Singleton<PathManager>
    {
    public:
        ~PathManager();

        static void    Initialize();
        static UString AssetPath();

    private:
        static UString _AssetPath;
    };
}

#endif
