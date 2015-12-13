/**
**    Vixen Engine
**    Copyright(c) 2015 Matt Guerrette
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
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
    std::string PathManager::_AssetPath = "";
    std::string PathManager::_ScenePath = "";
    std::string PathManager::_ModelPath = "";
    std::string PathManager::_MaterialPath = "";
    std::string PathManager::_ShaderPath = "";
    std::string PathManager::_ScriptPath = "";
    std::string PathManager::_PrefabPath = "";

    PathManager::~PathManager()
    {

    }

    void PathManager::Initialize()
    {
        using namespace tinyxml2;

        //Open Environment Config File
        File* envFile = FileManager::OpenFile(os_exec_dir() + "vixen.env", FileMode::ReadBinary);

        XMLDOC document;
        XMLError err = document.LoadFile(envFile->Handle());
        std::string errMsg;
        if (XMLErrCheck(err, errMsg)) {
            DebugPrintF("Env file failed to load: %s\n",
                errMsg.c_str());
            return;
        }

        const XMLElement* envElement = document.FirstChildElement("env");
        const XMLElement* assetPathElement = envElement->FirstChildElement("asset-path");

        _AssetPath += assetPathElement->Attribute("value");
        _AssetPath = os_path(_AssetPath);

        _ScenePath = _AssetPath + "Scenes/";
        _ScenePath = os_path(_ScenePath);

        _ModelPath = _AssetPath + "Models/";
        _ModelPath = os_path(_ModelPath);

        _ShaderPath = _AssetPath + "Shaders/";
#ifdef VIX_SYS_WINDOWS
        _ShaderPath += "DirectX/";
#endif
        _ShaderPath = os_path(_ShaderPath);


        _MaterialPath = _AssetPath + "Materials/";
        _MaterialPath = os_path(_MaterialPath);

        _ScriptPath = _AssetPath + "Scripts/";
        _ScriptPath = os_path(_ScriptPath);

        _PrefabPath = _AssetPath + "Prefabs/";
        _PrefabPath = os_path(_PrefabPath);

        FileManager::CloseFile(envFile);
    }

    void PathManager::DeInitialize()
    {

    }

    std::string PathManager::AssetPath()
    {
        return _AssetPath;
    }

    std::string PathManager::ScenePath()
    {
        return _ScenePath;
    }

    std::string PathManager::ModelPath()
    {
        return _ModelPath;
    }

    std::string PathManager::ShaderPath()
    {
        return _ShaderPath;
    }

    std::string PathManager::ScriptPath()
    {
        return _ScriptPath;
    }

    std::string PathManager::MaterialPath()
    {
        return _MaterialPath;
    }

    std::string PathManager::PrefabPath()
    {
        return _PrefabPath;
    }
}
