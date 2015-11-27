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


#ifndef VIX_GLTEXTUREBATCHER_H
#define VIX_GLTEXTUREBATCHER_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_stringutil.h>
#include <vix_glshaderprogram.h>
#include <vix_glbuffers.h>
#include <vix_gltexture.h>
#include <vix_glm.h>
#include <vix_glcamera2d.h>

namespace Vixen {

	//////////////////////////////////////////////////////////////////////////
	// DEFAULT VERTEX / FRAGMENT SHADERS
	//////////////////////////////////////////////////////////////////////////

	static const UString UNIFORM_PROJECTION = UString(VTEXT("gProjection"));
	static const UString UNIFORM_SAMPLER = UString(VTEXT("gSampler"));
	static const UString OUT_TEXCOORD = UString(VTEXT("TexCoord0"));
	static const UString OUT_COLOR = UString(VTEXT("Color"));
	static const UString DEF_VERT_SHADER = UString(VTEXT("#version ")) + VTEXT("330\n\n\n") +
		VTEXT("layout(location = 0) in vec2 vPosition;\n") +
		VTEXT("layout(location = 1) in vec4 vColor;\n") +
		VTEXT("layout(location = 2) in vec2 vTexCoord;\n") +
		VTEXT("out vec2 ") + OUT_TEXCOORD + VTEXT(";\n") +
		VTEXT("out vec4 ") + OUT_COLOR + VTEXT(";\n") +
		VTEXT("uniform mat4 ") + UNIFORM_PROJECTION + VTEXT(";\n") +
		VTEXT("void main()\n") +
		VTEXT("{\n") +
		VTEXT("gl_Position = ") + UNIFORM_PROJECTION +
		VTEXT(" * ") + VTEXT("vec4(vPosition, 0.0, 1.0);\n") + OUT_TEXCOORD + VTEXT(" = ") +
		VTEXT("vTexCoord;\n") + OUT_COLOR + VTEXT(" = ") + VTEXT("vColor;\n") + VTEXT("}\n");

	static const UString DEF_FRAG_SHADER = UString(VTEXT("#version ")) + VTEXT("330\n\n\n") +
		VTEXT("in vec2 ") + OUT_TEXCOORD + VTEXT(";\n") +
		VTEXT("in vec4 ") + OUT_COLOR + VTEXT(";\n") +
		VTEXT("uniform sampler2D ") + UNIFORM_SAMPLER + VTEXT(";\n\n") +
		VTEXT("uniform float gAlpha;\n\n") +
		VTEXT("void main()\n") + VTEXT("{\n\n") +
		VTEXT("gl_FragColor = ") + VTEXT("texture2D(") + UNIFORM_SAMPLER + VTEXT(",") + OUT_TEXCOORD +
		VTEXT(".st) * ") + OUT_COLOR + VTEXT(" * gAlpha") + VTEXT(";\n") +
		VTEXT("}\n");

	enum class BatchSortMode
	{
		IMMEDITATE,
		DEFERED,
		BACK_TO_FRONT,
		FRONT_TO_BACK
	};

	struct BatchInfo
	{
		float x, y;
		float r, g, b, a;
		float sX, sY, sW, sH;
		float originX, originY;
		float scaleX, scaleY;
		float rotation;
		float depth;
		float alpha;
	};

	struct Vertex2D
	{
		float x, y;
		float r, g, b, a;
		float u, v;

		Vertex2D() {
			x = 0; y = 0;
			r = 0; g = 0; b = 0; a = 0;
			u = 0; v = 0;
		}

		Vertex2D(float _x, float _y,
			float _r, float _g, float _b, float _a,
			float _u, float _v)
		{
			x = _x; y = _y;
			r = _r; g = _g; b = _b; a = _a;
			u = _u; v = _v;
		}

		static void Enable(bool flag)
		{
			if (flag) {
				glEnableVertexAttribArray(0); //pos
				glEnableVertexAttribArray(1); //color
				glEnableVertexAttribArray(2); //tex
			}
			else {
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
			}
		}

		static void Render(GLsizei index_cnt)
		{
			size_t stride = sizeof(Vertex2D);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 2; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 4; //update offset
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(GL_TRIANGLES, index_cnt, GL_UNSIGNED_SHORT, NULL);
		}
	};

	class VIX_API GLTextureBatcher
	{
	public:
		GLTextureBatcher(GLCamera2D* camera);

		~GLTextureBatcher();

		/*prepare batcher for rendering*/
		void Begin(BatchSortMode mode);

		/*render texure*/
		void Draw(Texture* texture, BatchInfo info);

		/*flush batched textures*/
		void End();

	private:
		/*shader program*/
		GLShaderProgram*       m_program;

		/*sort mode*/
		BatchSortMode          m_sortMode;

		/*number of textures rendered*/
		size_t                 m_textureCount;

		/*batch info collection*/
		std::vector<BatchInfo> m_textures;

		/*currently rendered texture*/
		GLTexture*               m_texture;

		/*Vertex buffer*/
		GLVertexBuffer<Vertex2D>*  m_vBuffer;

		/*Index buffer*/
		GLIndexBuffer*             m_iBuffer;

		/*camera*/
		GLCamera2D*              m_camera;

		/*alpha render val*/
		float                    m_alpha;

		/*Begin/End flag*/
		bool                      m_BEFlag;

		GLuint                      m_vao;

		/*-----------private utility functions-----------*/


		/*INITIALIZE SHADER PROGRAM*/
		ErrCode init_shader_program();

		/*FLUSH BUFFERED TEXTURES*/
		void flush();

		/*SORT TEXTURES BASED ON BATCH SORT MODE*/
		void sort_textures();

		/*BUILD TEXTURE FOR RENDERING*/
		void build_texture(BatchInfo info, size_t index);

		/*RENDER BATCHED TEXTURES*/
		void render_textures();

	private:

		/*STATIC CONSTANTS*/

		static const size_t MAX_BATCH_SIZE = 1048;
		static const size_t MIN_BATCH_SIZE = 128;
		static const size_t VERTS_PER_TEX = 4;
		static const size_t INDICES_PER_TEX = 6;
		static const size_t INIT_QUEUE_SIZE = 64;
		static const size_t MAX_VERT_COUNT = MAX_BATCH_SIZE * VERTS_PER_TEX;
		static const size_t MAX_INDEX_COUNT = MAX_BATCH_SIZE * INDICES_PER_TEX;
	};

}

#endif
