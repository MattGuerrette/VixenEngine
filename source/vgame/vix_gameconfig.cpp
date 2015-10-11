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

#include <vix_gameconfig.h>
#include <vix_stringutil.h>
#include <vix_debugutil.h>
#include <vix_filemanager.h>

namespace Vixen {

	GameConfig::GameConfig()
	{
		LoadConfig();
	}

	bool GameConfig::LoadConfig()
	{
		using namespace tinyxml2;


        //Open Environment Config File
        FILE* configFile = FileManager::OpenFile(os_exec_dir() + VTEXT("vtest.config"))->Handle();

		XMLDOC document;
        XMLError err = document.LoadFile(configFile);
		UString errMsg;
		if (XMLErrCheck(err, errMsg)) {
			DebugPrintF(VTEXT("GameConfig file failed to load: %s\n"),
				errMsg.c_str());
            FileManager::CloseFile(os_exec_dir() + VTEXT("vtest.config"));
			return false;
		}

		/*Parse config file*/
		if (!ParseConfig(document)) {
			DebugPrintF(VTEXT("GameConfig failed to parse"));
            FileManager::CloseFile(os_exec_dir() + VTEXT("vtest.config"));
            return false;
		}

        FileManager::CloseFile(os_exec_dir() + VTEXT("vtest.config"));
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
