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

#include <vix_gameconfig.h>
#include "vix_stringutil.h"
#include "vix_debugutil.h"
#include "vix_filemanager.h"

namespace Vixen {

	GameConfig::GameConfig()
	{
		LoadConfig();
	}

	bool GameConfig::LoadConfig()
	{
		using namespace tinyxml2;


        //Open Environment Config File
        File* configFile = FileManager::OpenFile(os_exec_dir() + VTEXT("vixen.config"), FileMode::ReadBinary);
        if (!configFile)
            return false;

		XMLDOC document;
        XMLError err = document.LoadFile(configFile->Handle());
		UString errMsg;
		if (XMLErrCheck(err, errMsg)) {
			DebugPrintF(VTEXT("GameConfig file failed to load: %s\n"),
				errMsg.c_str());
            FileManager::CloseFile(configFile);
			return false;
		}

		/*Parse config file*/
		if (!ParseConfig(document)) {
			DebugPrintF(VTEXT("GameConfig failed to parse"));
            FileManager::CloseFile(configFile);
            return false;
		}

        FileManager::CloseFile(configFile);
		return true;
	}

	bool GameConfig::ParseConfig(const XMLDOC& doc)
	{
		/*Parse Window Attributes*/
		m_windowArgs = ParseWindow(doc);

		return true;
	}

	SDL_GW_Params GameConfig::ParseWindow(const XMLDOC& doc)
	{
		using namespace tinyxml2;

		SDL_GW_Params params;
		const XMLElement* gameElement = doc.FirstChildElement("game");
		const XMLElement* windowElement = gameElement->FirstChildElement("window");
#ifdef UNICODE /*this could change in future*/
		UConverter convert;
		params.title = convert.from_bytes(windowElement->Attribute("title"));
#else
		params.title = windowElement->Attribute("title");
#endif
		params.x = windowElement->IntAttribute("x");
		params.y = windowElement->IntAttribute("y");
		params.width = windowElement->IntAttribute("width");
		params.height = windowElement->IntAttribute("height");

       /* const XMLElement* rendererElement = gameElement->FirstChildElement("renderer");
        const char* renderer = rendererElement->Attribute("type");
        if (!strcmp(renderer, "DirectX"))
            params.renderer = SDL_GW_Renderer::OPENGL;
        else
            params.renderer = SDL_GW_Renderer::DIRECTX;*/

		return params;
	}

	SDL_GW_Params GameConfig::WindowArgs() const
	{
		return m_windowArgs;
	}

}
