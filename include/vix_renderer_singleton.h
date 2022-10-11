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

#ifndef VIX_RENDERER_SINGLETON_H
#define VIX_RENDERER_SINGLETON_H

#include "vix_platform.h"
#include "vix_singleton.h"
#include "vix_renderer.h"

namespace Vixen {

    class VIX_API Renderer : public Singleton<Renderer>
    {
    public:
        static bool		    Initialize(void* HWND);

        static void		    DeInitialize();

        static void         InitializeSpriteBatch();

        static void         SetClearColor(const Color& c);

        static void         ClearBuffer(ClearArgs args);

        static void         SwapBuffers();

        static void         Render2DText(Font* font, UString text, const Vector2& position);

        static void         ResizeBuffers(uint32_t width, uint32_t height);

		static void			RenderFinal();

		static void			RenderDeferred();
		
		static void			RenderLights(ICamera3D* camera, Model* model, std::vector<PointLight*>& lights);

		static void			RenderLights(ICamera3D* camera, Model* model, std::vector<SpotLight*>& lights);

        static IRenderer*   Handle();

		static ICamera2D*   Camera2D();
    private:
        IRenderer*  m_renderer;
    };

}

#endif
