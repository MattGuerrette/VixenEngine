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

#include <vix_pathmanager.h>
#include <vix_tinyxml.h>
#include <vix_debugutil.h>
#include <vix_osutil.h>
#include <vix_filemanager.h>

namespace Vixen
{
    UString PathManager::_AssetPath = VTEXT("");
    UString PathManager::_ScenePath = VTEXT("");
    UString PathManager::_ModelPath = VTEXT("");
    UString PathManager::_ShaderPath = VTEXT("");
    UString PathManager::_ScriptPath = VTEXT("");
	UString PathManager::_PrefabPath = VTEXT("");

    PathManager::~PathManager()
    {

    }

    void PathManager::Initialize()
    {
        using namespace tinyxml2;

        //Open Environment Config File
        File* envFile = FileManager::OpenFile(os_exec_dir() + VTEXT("vixen.env"));

        XMLDOC document;
        XMLError err = document.LoadFile(envFile->Handle());
		UString errMsg;
		if (XMLErrCheck(err, errMsg)) {
			DebugPrintF(VTEXT("Env file failed to load: %s\n"),
				errMsg.c_str());
			return;
		}

        const XMLElement* envElement = document.FirstChildElement("env");
        const XMLElement* assetPathElement = envElement->FirstChildElement("asset-path");

        _AssetPath += UStringFromCharArray(assetPathElement->Attribute("value"));
        _AssetPath = os_path(_AssetPath);

        _ScenePath = _AssetPath + VTEXT("Scenes/");
        _ScenePath = os_path(_ScenePath);

        _ModelPath = _AssetPath + VTEXT("Models/");
        _ModelPath = os_path(_ModelPath);

        _ShaderPath = _AssetPath + VTEXT("Shaders/");
#ifdef VIX_SYS_WINDOWS
        _ShaderPath += VTEXT("DirectX/");
#endif
        _ShaderPath = os_path(_ShaderPath);

        _ScriptPath = _AssetPath + VTEXT("Scripts/");
        _ScriptPath = os_path(_ScriptPath);

		_PrefabPath = _AssetPath + VTEXT("Prefabs/");
		_PrefabPath = os_path(_PrefabPath);

        FileManager::CloseFile(envFile);
    }

    void PathManager::DeInitialize()
    {
        
    }

    UString PathManager::AssetPath()
    {
        return _AssetPath;
    }

    UString PathManager::ScenePath()
    {
        return _ScenePath;
    }

    UString PathManager::ModelPath()
    {
        return _ModelPath;
    }

    UString PathManager::ShaderPath()
    {
        return _ShaderPath;
    }

    UString PathManager::ScriptPath()
    {
        return _ScriptPath;
    }

	UString PathManager::PrefabPath()
	{
		return _PrefabPath;
	}
}
