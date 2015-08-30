/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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
