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

#ifndef VIX_RENDERER_H
#define VIX_RENDERER_H

#include <vix_platform.h>
#include <vix_color.h>
#include <vix_rectangle.h>
#include <vix_texture.h>
#include <vix_model.h>
#include <vix_camera3d.h>
#include <vix_vector2.h>
#include <vix_font.h>

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

	};

}

#endif
