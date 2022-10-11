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

#ifndef VIX_RENDERER_H
#define VIX_RENDERER_H

#include "vix_platform.h"
#include "vix_color.h"
#include "vix_rectangle.h"
#include "vix_texture.h"
#include "vix_model.h"
#include "vix_camera3d.h"
#include "vix_vector2.h"
#include "vix_font.h"
#include "vix_camera2d.h"
#include "vix_light.h"

namespace Vixen {

	enum class ClearArgs
	{
		COLOR_BUFFER,
		DEPTH_BUFFER,
		STENC_BUFFER,
		COLOR_DEPTH_BUFFER,
		COLOR_STENCIL_BUFFER,
		DEPTH_STENCIL_BUFFER,
		COLOR_DEPTH_STENCIL_BUFFER,
	};


	class VIX_API IRenderer
	{
	public:
        virtual ~IRenderer() { };

        //RenderType enum
        //
        // Used for type checking renderer
        enum class RendererType
        {
            DIRECTX,
            OPENGL
        };

        virtual bool    VInitialize() = 0;
        virtual void    VDeInitialize() = 0;
		virtual void    VSetClearColor(const Color& c) = 0;
		virtual void    VClearBuffer(ClearArgs args) = 0;
        virtual void    VSwapBuffers() = 0;
        virtual void    VAttachNativeHandle(void* handle) = 0;
        virtual void    VInitializeSpriteBatch() = 0;
        virtual void    VRenderTexture2D(Texture* texture, const Vector2& pos, const Rect& source) = 0;
        virtual void    VRenderText2D(Font* font, UString text, const Vector2& pos) = 0;
        virtual void    VResizeBuffers(uint32_t width, uint32_t height) = 0;
		virtual void	VRenderBackBuffer() = 0;
		virtual void    VBeginDeferred() = 0;
		virtual void    VLightPass(ICamera3D* camera, Model* model, std::vector<PointLight*>& lights) = 0;
		virtual void    VLightPass(ICamera3D* camera, Model* model, std::vector<SpotLight*>& lights) = 0;
		virtual void    VLightPass(ICamera3D* camera, Model* model) = 0;
		virtual ICamera2D* VCamera2D() = 0;

	};

}

#endif
