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
	UString PathManager::_MaterialPath = VTEXT("");
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
        File* envFile = FileManager::OpenFile(os_exec_dir() + VTEXT("vixen.env"), FileMode::ReadBinary);

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


		_MaterialPath = _AssetPath + VTEXT("Materials/");
		_MaterialPath = os_path(_MaterialPath);

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

	UString PathManager::MaterialPath()
	{
		return _MaterialPath;
	}

	UString PathManager::PrefabPath()
	{
		return _PrefabPath;
	}
}
