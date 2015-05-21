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

	ErrCode GLRenderer::VInit()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		glewExperimental = GL_TRUE;
		/*initialize glew*/
		GLenum glewErr = glewInit();
		if (glewErr != GLEW_OK) {
			DebugPrintF(VTEXT("Glew failed to initialize: %s\n"),
				    glewGetErrorString(glewErr));
			return ErrCode::ERR_GLEW_INIT_FAIL;
		}

		/*SetFaceCulling(FaceCulling::BACK);
		SetFaceWinding(FaceWinding::CW);
		SetRenderMode(RenderMode::FILL);*/

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);


		/*init camera2D*/
		m_camera2D = new GLCamera2D(0, 1280, 0, 800);

		/*init 3d camera*/
		m_camera3D = new GLCamera3D;
		m_camera3D->SetPerspective(static_cast<float>(800)/
			                       static_cast<float>(600), 45.0f, -1000.0f, 1000.0f);
		m_camera3D->SetView(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		/*init textureBatcher*/
		m_Render2DBatcher = new GLTextureBatcher(m_camera2D);

		return error;
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

	GLCamera3D* GLRenderer::Camera3D() const
	{
		return m_camera3D;
	}

	GLCamera2D* GLRenderer::Camera2D() const
	{
		return m_camera2D;
	}

	void GLRenderer::VShutDown()
	{
		delete m_camera2D;
		delete m_camera3D;
		delete m_Render2DBatcher;
	}


	void GLRenderer::VSetProjection(Mat4 projection)
	{

	}

	void GLRenderer::VSetClientRect(const Rect& client)
	{
		m_client = client;

        /*update viewport and camera*/
		glViewport(0, 0, m_client.w, m_client.h);
		m_camera3D->SetPerspective((float)m_client.w / (float)m_client.h, 45.0f, 0.05f, 1000.0f);
		m_camera2D->SetBounds(0, (float)m_client.w, 0, (float)m_client.h);
	}

	void GLRenderer::Render2DTexture(GLTexture* texture,
									 const Vector2&  position,
									 const Rect&     source,
									 const Vector2&  origin,
									 const Vector2&  scale,
									 float           rotation,
									 float           alpha,
									 const Color&    color,
									 float           depth)
	{
		float x = position.x;
		if(position.x == -1) {
			float midX = static_cast<float>((m_client.w - texture->getWidth())/2);
			float midXAbs = abs(midX);
			x = midXAbs;
		}
		float y = position.y;
		if(position.y == -1) {
			float midY = static_cast<float>((m_client.h - texture->getHeight())/2);
			float midYAbs = abs(midY);
			y = midYAbs;
		}
		BatchInfo info;
		info.x = x;
		info.y = y;
		info.sX = static_cast<float>(source.x);
		info.sY = static_cast<float>(source.y);
		info.sW = static_cast<float>(source.w);
		info.sH = static_cast<float>(source.h);
		info.originX = origin.x;
		info.originY = origin.y;
		info.scaleX = scale.x;
		info.scaleY = scale.y;
		info.rotation = Math::ToRadians(rotation);
		info.r = color.r;
		info.g = color.g;
		info.b = color.b;
		info.a = color.a;
		info.alpha = alpha;
		info.depth = depth;

		m_Render2DBatcher->Begin(BatchSortMode::IMMEDITATE);
		/*batch using info*/
		m_Render2DBatcher->Draw(texture, info);
		m_Render2DBatcher->End();
	}

	void GLRenderer::Render2DText(BMFont * font, UString text, const Vector2 & position, float alpha, const Color & color)
	{
		m_Render2DBatcher->Begin(BatchSortMode::IMMEDITATE);

		float x = position.x;
		if(position.x == -1) {
			float midX = static_cast<float>((m_client.w - font->Bounds(text).w)/2);
			x = midX;
		}
		float y = position.y;
		if(position.y == -1) {
			float midY = static_cast<float>((m_client.h - font->Bounds(text).h)/2);
			y = midY;
		}

		float dx = x;
		float dy = y;
		for (UChar &c : text)
		{
			if (c == '\n')
			{
				dx = x;
				dy += font->FontFile().common.lineHeight;
				continue;
			}

			BMFontChar fc;
			if (font->FindChar(c, fc))
			{
				BatchInfo info;
				info.x = dx + fc.xOffset;
				info.y = dy + fc.yOffset;
				info.sX = (float)fc.x;
				info.sY = (float)fc.y;
				info.sW = (float)fc.width;
				info.sH = (float)fc.height;
				info.originX = 0;
				info.originY = 0;
				info.scaleX = 1;
				info.scaleY = 1;
				info.rotation = 0.0f;
				info.r = color.r;
				info.g = color.g;
				info.b = color.b;
				info.a = color.a;
				info.alpha = alpha;
				info.depth = 1;


				m_Render2DBatcher->Draw(font->PageTexture(fc.page), info);

				dx += fc.xAdvance;
			}
		}

		m_Render2DBatcher->End();
	}

}
