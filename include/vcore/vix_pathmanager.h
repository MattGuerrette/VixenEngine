/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
        static UString ShaderPath();
        static UString ScriptPath();
		static UString PrefabPath();

    private:
        static UString _AssetPath;
        static UString _ScenePath;
        static UString _ModelPath;
        static UString _ShaderPath;
        static UString _ScriptPath;
		static UString _PrefabPath;
    };
}

#endif
