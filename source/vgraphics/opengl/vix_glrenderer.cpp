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

#include <vix_glrenderer.h>
#include <vix_gl.h>
#include <vix_debugutil.h>
#include <vix_math.h>
#include <vix_freeimage.h>

namespace Vixen {

	void GLRenderer::VSetClearColor(const Color& c)
	{
		//set clear color
		glClearColor(c.r, c.g, c.b, c.a);
	}

	bool GLRenderer::VInitialize()
	{
		glewExperimental = GL_TRUE;
		/*initialize glew*/
		GLenum glewErr = glewInit();
		if (glewErr != GLEW_OK) {
			DebugPrintF(VTEXT("Glew failed to initialize: %s\n"),
				    glewGetErrorString(glewErr));
			return false;
		}

		return true;
	}

	void GLRenderer::VInitializeSpriteBatch()
	{

	}

	void GLRenderer::VResizeBuffers(uint32_t width, uint32_t height)
	{

	}

	ICamera2D* GLRenderer::VCamera2D()
	{
		return NULL;
	}

	void GLRenderer::VClearBuffer(ClearArgs args)
	{
		switch (args)
		{
		case ClearArgs::COLOR_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT);
			break;
		case ClearArgs::DEPTH_BUFFER:
			glClear(GL_DEPTH_BUFFER_BIT);
			break;
		case ClearArgs::STENC_BUFFER:
			glClear(GL_STENCIL_BUFFER_BIT);
			break;
		case ClearArgs::COLOR_DEPTH_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;

		case ClearArgs::COLOR_STENCIL_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			break;

		case ClearArgs::DEPTH_STENCIL_BUFFER:
			glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			break;

		case ClearArgs::COLOR_DEPTH_STENCIL_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			break;
		}
	}


	void GLRenderer::VDeInitialize()
	{

	}

	void GLRenderer::VSwapBuffers()
	{

	}

	void    GLRenderer::VRenderTexture2D(Texture* texture, const Vector2& pos, const Rect& source)
	{

	}

	void    GLRenderer::VRenderText2D(Font* font, UString text, const Vector2& pos)
	{

	}

	void    GLRenderer::VRenderModel(Model* model)
	{

	}

	void GLRenderer::VAttachNativeHandle(void* handle)
	{

	}
}
