/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
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
