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

#include <vix_renderer.h>

namespace Vixen {

	void Renderer::SetFaceCulling(FaceCulling culling)
	{
		if(m_renderOptions.mFaceCulling != culling) {
			m_renderOptions.mFaceCulling = culling;
			m_renderOptionsState[RenderOptions::FC_STATE] = true;
		}
	}

	void Renderer::SetFaceWinding(FaceWinding winding)
	{
		if(m_renderOptions.mFaceWinding != winding) {
			m_renderOptions.mFaceWinding = winding;
			m_renderOptionsState[RenderOptions::FW_STATE] = true;
		}
	}

	void Renderer::SetRenderMode(RenderMode mode)
	{
		if(m_renderOptions.mRenderMode != mode) {
			m_renderOptions.mRenderMode = mode;
			m_renderOptionsState[RenderOptions::RM_STATE] = true;
		}
	}

	void Renderer::UpdateRenderOptions()
	{
		if(m_renderOptionsState[RenderOptions::FW_STATE]) {
			VApplyFaceWinding(); //apply new FW state
			m_renderOptionsState[RenderOptions::FW_STATE] = false;
		}

		if(m_renderOptionsState[RenderOptions::FC_STATE]) {
			VApplyFaceCulling();
			m_renderOptionsState[RenderOptions::FC_STATE] = false;
		}

		if(m_renderOptionsState[RenderOptions::RM_STATE]) {
			VApplyRenderMode();
			m_renderOptionsState[RenderOptions::RM_STATE] = false;
		}
	}

    Renderer::RendererType Renderer::Type()
    {
        return m_type;
    }

    ICamera3D* Renderer::Camera3D()
    {
        return m_camera3D;
    }

}
