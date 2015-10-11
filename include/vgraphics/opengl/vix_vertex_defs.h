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

#ifndef VIX_VERTEX_DEFS_H
#define VIX_VERTEX_DEFS_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>

namespace Vixen {

	struct PositionColor
	{
		float x, y, z;
		float r, g, b, a;

		PositionColor() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f;
		}

		PositionColor(float _x, float _y, float _z,
			                float _r, float _g, float _b, float _a)
		{
			x = _x; y = _y; z = _z;
			r = _r; g = _g; b = _b; a = _a;
		}

		static void Enable(bool flag)
		{
			if(flag) {
				glEnableVertexAttribArray(0); //position
				glEnableVertexAttribArray(1); //color
			} else {
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
			}
		}

		static void RenderElements(GLsizei index_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(PositionColor);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(render_mode, index_cnt, GL_UNSIGNED_SHORT, NULL);

		}

		static void RenderArrays(GLsizei vertex_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(PositionColor);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawArrays(render_mode, 0, vertex_cnt);
		}
	};

	struct PositionTexture
	{
		float x, y, z;
		float u, v;

		PositionTexture() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			u = 0.0f; v = 0.0f;
		}

		PositionTexture(float _x, float _y, float _z,
			                  float _u, float _v)
		{
			x = _x; y = _y; z = _z;
			u = _u; v = _v;
		}

		static void Enable(bool flag)
		{
			if (flag) {
				glEnableVertexAttribArray(0); //position
				glEnableVertexAttribArray(1); //texture
			}
			else {
				glDisableVertexAttribArray(0); //position
				glDisableVertexAttribArray(1); //texture
			}
		}

		static void RenderArrays(GLsizei vertex_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(PositionColor);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawArrays(render_mode, 0, vertex_cnt);
		}

		static void RenderElements(GLsizei index_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(PositionTexture);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(render_mode, index_cnt, GL_UNSIGNED_SHORT, NULL);
		}
	};

	struct PositionNormalTexture
	{
		float x, y, z;		//position
		float nx, ny, nz;	//normal
		float u, v;			//uv
		float tx, ty, tz;	//tangent

		PositionNormalTexture() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			nx = 0.0f; ny = 0.0f; nz = 0.0f;
			u = 0.0f; v = 0.0f;
			tx = 0.0f; ty = 0.0f; tz = 0.0f;
		}

		PositionNormalTexture(float _x, float _y, float _z,
							  float _nx, float _ny, float _nz,
			                  float _u, float _v,
							  float _tx, float _ty, float _tz)
		{
			x = _x; y = _y; z = _z;
			nx = _nx; ny = _ny; nz = _nz;
			u = _u; v = _v;
			tx = _tx; ty = _ty; tz = _tz;
		}

		static void Enable(bool flag)
		{
			if(flag) {
				glEnableVertexAttribArray(0); //position
				glEnableVertexAttribArray(1); //normal
				glEnableVertexAttribArray(2); //texture
			} else {
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
			}
		}

		static void RenderArrays(GLsizei vertex_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(PositionNormalTexture);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*NORMAL*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 3;
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TANGENT*/
			offset += sizeof(float) * 2;
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawArrays(render_mode, 0, vertex_cnt);
		}

		static void RenderElements(GLsizei index_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(PositionNormalTexture);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*NORMAL*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 3;
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TANGENT*/
			offset += sizeof(float) * 2;
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(render_mode, index_cnt, GL_UNSIGNED_SHORT, NULL);

		}
	};

	struct PositionColorTexture
	{
		float x, y, z;
		float r, g, b, a;
		float u, v;

		PositionColorTexture() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f;
			u = 0.0f; v = 0.0f;
		}

		PositionColorTexture(float _x, float _y, float _z,
			float _r, float _g, float _b, float _a,
			float _u, float _v)
		{
			x = _x; y = _y; z = _z;
			r = _r; g = _g; b = _b; a = _a;
			u = _u; v = _v;
		}

		static void Enable(bool flag)
		{
			if (flag) {
				glEnableVertexAttribArray(0); //position
				glEnableVertexAttribArray(1); //color
				glEnableVertexAttribArray(2); //texture
			}
			else {
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
			}
		}

		static void Render(GLsizei index_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(PositionColorTexture);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 4;
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(render_mode, index_cnt, GL_UNSIGNED_SHORT, NULL);
		}
	};

	namespace VBuffers
	{
		/*USEFULL TYPEDEFS FOR VERTEX TYPES*/
		typedef GLVertexBuffer<PositionColor>			PCVBuffer;
		typedef GLVertexBuffer<PositionTexture>			PTVBuffer;
		typedef GLVertexBuffer<PositionColorTexture>	PCTVBuffer;
		typedef GLVertexBuffer<PositionNormalTexture>   PNTVBuffer;
	}
}

#endif
