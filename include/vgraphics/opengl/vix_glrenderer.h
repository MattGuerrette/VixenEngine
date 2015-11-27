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

#ifndef VIX_GL_RENDERER_H
#define VIX_GL_RENDERER_H

#include <vix_platform.h>
#include <vix_renderer.h>
#include <vix_color.h>
#include <vix_camera2d.h>

namespace Vixen {

	class VIX_API GLRenderer : public IRenderer
	{
	public:

		bool    VInitialize();
        void    VDeInitialize();
		void    VInitializeSpriteBatch();
		void    VResizeBuffers(uint32_t width, uint32_t height);
		ICamera2D* VCamera2D();
		void    VSetClearColor(const Color& c);
		void    VClearBuffer(ClearArgs args);
        void    VSwapBuffers();
        void    VAttachNativeHandle(void* handle);
        void    VRenderTexture2D(Texture* texture, const Vector2& pos, const Rect& source);
    	void    VRenderText2D(Font* font, UString text, const Vector2& pos);
        void    VRenderModel(Model* model);

	};

}


#endif
