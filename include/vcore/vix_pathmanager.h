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
        static std::string AssetPath();
        static std::string ScenePath();
        static std::string ModelPath();
		static std::string MaterialPath();
        static std::string ShaderPath();
        static std::string ScriptPath();
		static std::string PrefabPath();

    private:
        static std::string _AssetPath;
        static std::string _ScenePath;
        static std::string _ModelPath;
		static std::string _MaterialPath;
        static std::string _ShaderPath;
        static std::string _ScriptPath;
		static std::string _PrefabPath;
    };
}

#endif
