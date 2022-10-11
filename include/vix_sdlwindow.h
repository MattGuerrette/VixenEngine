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

#ifndef VIX_SDLWINDOW_H
#define VIX_SDLWINDOW_H

#include "vix_platform.h"
#include "vix_gamewindow.h"
#include "vix_time.h"
#include "vix_sdlinput.h"
#ifdef VIX_SYS_WINDOWS
#include <SDL.h>
#include <SDL_syswm.h>
#undef main
#elif defined(VIX_SYS_LINUX)
#include <SDL2/SDL.h>
#endif



namespace Vixen {

	enum class SDL_GW_Flags
	{
		SDL_GW_FULLSCREEN,
		SDL_GW_FULLSCREEN_DESKTOP,
		SDL_GW_OPENGL,
		SDL_GW_HIDDEN,
		SDL_GW_BORDERLESS,
		SDL_GW_RESIZEABLE,
		SDL_GW_MINIMIZED,
		SDL_GW_INPUT_GRABBED,
		SDL_GW_ALLOW_HIGHDPI
	};

    enum class SDL_GW_Renderer
    {
        DIRECTX,
        OPENGL
    };

	struct VIX_API SDL_GW_Params
	{
		UString title;
		int x;
		int y;
		int width;
		int height;
		Uint32 flags;
        SDL_GW_Renderer renderer;
	};

	class VIX_API SDLGameWindow : public GameWindow
	{
	public:
		SDLGameWindow(const SDL_GW_Params& params);

		~SDLGameWindow();

		bool                VInit()                                override;
		void                VSetVisible(bool flag)                 override;
		void                VSetFullscreen(bool flag)              override;
		void                VSwapBuffers()                         override;
		const UString&      VGetTitle()                            override;
		const Rect          VGetClientBounds()                     override;
		bool                VIsRunning()                           override;
		bool                VIsHidden()                            override;
		bool                VIsPaused()                            override;
		void                VClose()                               override;
		void                VToggleCursor()                        override;
		void                VTogglePaused()                        override;
		void				VTrapCursorCenter()                    override;
        void                VSetTitle(std::string title)           override;
        void*               VNativeHandle()                        override;

        bool                VRunning()                             override;

        void                VPollEvents()                          override;
        void                VPollNextFrame()                       override;


        void                VStartTextCapture()                    override;
        std::string         VInputBuffer()                         override;
        void                VStopTextCapture()                     override;

        IKeyboardState*     VKeyboardState()                       override;
        IMouseState*        VMouseState()                          override;
		SDLControllerState* VControllerState();

		void                OutputDisplayModes();

	private:
		SDL_Window*			m_windowHandle;
		SDL_GLContext		m_context;
        SDL_GW_Params		m_params;
        void*               m_nativeHandle;
		int					m_controllerIndeces[4];
		SDL_GameController* m_controllers[4];
		int					GetPlayerFromControllerIndex(int controllerIndex);
	};

}

#endif
