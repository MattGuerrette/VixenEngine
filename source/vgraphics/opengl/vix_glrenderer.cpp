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

	void GLRenderer::VApplyFaceCulling()
	{
		switch(m_renderOptions.mFaceCulling)
		{
		case FaceCulling::BACK:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;

		case FaceCulling::FRONT:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;

		case FaceCulling::BOTH:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT_AND_BACK);
			break;

		case FaceCulling::NONE:
			glDisable(GL_CULL_FACE);
			break;
		}
	}

	void GLRenderer::VApplyFaceWinding()
	{
		switch(m_renderOptions.mFaceWinding)
		{
		case FaceWinding::CW:
			glFrontFace(GL_CW);
			break;

		case FaceWinding::CCW:
			glFrontFace(GL_CCW);
			break;
		}
	}

	void GLRenderer::VApplyRenderMode()
	{
		switch(m_renderOptions.mRenderMode)
		{
		case RenderMode::FILL:
			switch(m_renderOptions.mFaceCulling)
			{
			case FaceCulling::FRONT:
				glPolygonMode(GL_BACK, GL_FILL);
				break;

			case FaceCulling::BACK:
				glPolygonMode(GL_FRONT, GL_FILL);
				break;

			case FaceCulling::NONE:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			}
			break;

		case RenderMode::WIREFRAME:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		}
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

	void GLRenderer::VRenderTexture2D(ITexture* texture, const Transform& trans, const Rect& source)
	{

	}

	void GLRenderer::VAttachNativeHandle(void* handle)
	{
		
	}
}
