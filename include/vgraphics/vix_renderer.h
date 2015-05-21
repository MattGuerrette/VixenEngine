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

#ifndef VIX_RENDERER_H
#define VIX_RENDERER_H

#include <vix_platform.h>
#include <vix_errglobals.h>
#include <vix_glm.h>
#include <vix_color.h>
#include <vix_rectangle.h>

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

	enum class FaceWinding
	{
		CW,
		CCW
	};

	enum class FaceCulling
	{
		FRONT,
		BACK,
		BOTH,
		NONE
	};

	enum class RenderMode
	{
		WIREFRAME,
		FILL
	};

	struct RenderOptions
	{
		enum RenderOptionStates
		{
			FW_STATE,
			FC_STATE,
			RM_STATE
		};

		FaceWinding mFaceWinding;
		FaceCulling mFaceCulling;
		RenderMode  mRenderMode;

		bool operator== (const RenderOptions& other) {
			return (mFaceWinding == other.mFaceWinding) &&
				   (mRenderMode == other.mRenderMode);
		}

		bool operator!= (const RenderOptions& other) {
			return !(*this == other);
		}

		static const size_t COUNT = 3;
	};

	class VIX_API IRenderer
	{
	public:

		virtual ErrCode VInit() = 0;
		virtual void    VShutDown() = 0;
		virtual void    VSetClearColor(const Color& c) = 0;
		virtual void    VClearBuffer(ClearArgs args) = 0;
		virtual void    VSetProjection(Mat4 p) = 0;
		virtual void    VSetClientRect(const Rect& client) = 0;
		virtual void    VApplyRenderMode() = 0;
		virtual void	VApplyFaceCulling() = 0;
		virtual void	VApplyFaceWinding() = 0;


		void UpdateRenderOptions();
		void SetRenderMode(RenderMode mode);
		void SetFaceCulling(FaceCulling culling);
		void SetFaceWinding(FaceWinding winding);

	protected:
		Rect							m_client;
		RenderOptions					m_renderOptions;
		bool                            m_renderOptionsState[RenderOptions::COUNT];
	};

}

#endif
