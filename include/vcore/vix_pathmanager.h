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
        static void    DeInitialize();
        static UString AssetPath();
        static UString ScenePath();
        static UString ModelPath();
		static UString MaterialPath();
        static UString ShaderPath();
        static UString ScriptPath();
		static UString PrefabPath();

    private:
        static UString _AssetPath;
        static UString _ScenePath;
        static UString _ModelPath;
		static UString _MaterialPath;
        static UString _ShaderPath;
        static UString _ScriptPath;
		static UString _PrefabPath;
    };
}

#endif
