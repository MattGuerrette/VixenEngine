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

#ifndef VIX_GL_RENDERER_H
#define VIX_GL_RENDERER_H

#include <vix_platform.h>
#include <vix_renderer.h>
#include <vix_color.h>
#include <vix_gltexturebatcher.h>
#include <vix_vector2.h>
#include <vix_rectangle.h>
#include <vix_glcamera2d.h>
#include <vix_glcamera3d.h>
#include <vix_bmfont.h>

namespace Vixen {

	class VIX_API GLRenderer : public IRenderer
	{
	public:

		ErrCode VInit()                            override;
		void    VShutDown()                        override;
		void    VSetClearColor(const Color& c)     override;
		void    VClearBuffer(ClearArgs args)       override;
		void    VSetProjection(Mat4 projection)    override;
		void    VSetClientRect(const Rect& client) override;
		void    VApplyFaceCulling()                override;
		void    VApplyFaceWinding()                override;
		void    VApplyRenderMode()                 override;

		void    Render2DTexture(GLTexture* texture,
								const Vector2&  position,
								const Rect&     source,
								const Vector2&  origin,
								const Vector2&  scale,
								float           rotation,
								float           alpha,
								const Color&    color,
								float           depth);

		void   Render2DText(BMFont* font,
			                UString text,
							const Vector2& position,
							float alpha,
							const Color&   color);

		GLCamera2D* Camera2D() const;
		GLCamera3D* Camera3D() const;

	private:
		Rect               m_clientInfo;
		GLCamera2D*        m_camera2D;
		GLCamera3D*        m_camera3D;
		GLTextureBatcher*  m_Render2DBatcher;
	};

}


#endif
