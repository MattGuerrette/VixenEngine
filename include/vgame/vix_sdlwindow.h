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

#ifndef VIX_SDLWINDOW_H
#define VIX_SDLWINDOW_H

#include <vix_platform.h>
#include <vix_gamewindow.h>
#include <vix_time.h>
#include <vix_sdlinput.h>
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
