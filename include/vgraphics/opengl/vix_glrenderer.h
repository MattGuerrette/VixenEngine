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


#ifndef VIX_GL_RENDERER_H
#define VIX_GL_RENDERER_H

#include <vix_platform.h>
#include <vix_renderer.h>
#include <vix_color.h>

namespace Vixen {

	class VIX_API GLRenderer : public IRenderer
	{
	public:

		bool    VInitialize();
		void    VInitializeSpriteBatch();
        void    VDeInitialize();
		void    VSetClearColor(const Color& c);
		void    VClearBuffer(ClearArgs args);
        void    VSwapBuffers();
        void    VAttachNativeHandle(void* handle);
		void    VRenderTexture2D(ITexture* texture, const Vector2& pos, const Rect& source);
        void    VRenderText2D(IFont* font, UString text, const Vector2& pos);
        void    VRenderModel(IModel* model);

	};

}


#endif
