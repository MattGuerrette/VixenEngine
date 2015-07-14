#include <vix_pathmanager.h>
#include <vix_tinyxml.h>
#include <vix_debugutil.h>
#include <vix_osutil.h>
#include <vix_filemanager.h>

namespace Vixen
{
    UString PathManager::_AssetPath = VTEXT("");

    PathManager::~PathManager()
    {

    }

    void PathManager::Initialize()
    {
        using namespace tinyxml2;

        //Open Environment Config File
        FileManager::OpenFile(os_exec_dir() + VTEXT("vixen.env"));

        //Access file
        FILE* envFile = FileManager::AccessFile(os_exec_dir() + VTEXT("vixen.env"))->Handle();

        XMLDOC document;
        XMLError err = document.LoadFile(envFile);
		UString errMsg;
		if (XMLErrCheck(err, errMsg)) {
			DebugPrintF(VTEXT("Env file failed to load: %s\n"),
				errMsg.c_str());
			return;
		}

        const XMLElement* envElement = document.FirstChildElement("env");
        const XMLElement* assetPathElement = envElement->FirstChildElement("asset-path");

        _AssetPath = assetPathElement->Attribute("value");
    }

    UString PathManager::AssetPath()
    {
        return _AssetPath;
    }

}
