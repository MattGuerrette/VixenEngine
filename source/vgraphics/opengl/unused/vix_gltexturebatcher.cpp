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

#include <vix_gltexturebatcher.h>
#include <vix_glm.h>
#include <vix_rectangle.h>
#include <algorithm>

namespace Vixen {

	GLTextureBatcher::GLTextureBatcher(GLCamera2D* camera)
	{
		m_vBuffer = new GLVertexBuffer<Vertex2D>(MAX_VERT_COUNT);
		m_iBuffer = new GLIndexBuffer(MAX_INDEX_COUNT);
		m_texture = NULL;
		m_textureCount = 0;
		m_camera = camera;
		m_alpha = 1.0f;


		//populate index buffer
		for (unsigned short i = 0, j = 0; i < MAX_BATCH_SIZE; i++, j += VERTS_PER_TEX)
		{
			//each sprite is made up of 6 indices, 3 per triangle, 2 tri's per sprite
			const std::array<unsigned short, INDICES_PER_TEX> temp =
			{
				0 + j, 1 + j, 2 + j,
				2 + j, 1 + j, 3 + j
			};
			size_t offset = m_iBuffer->get_stride() * i * INDICES_PER_TEX;
			m_iBuffer->set(offset, INDICES_PER_TEX, temp.data());
		}

		/*initialize shader program*/
		init_shader_program();
	}

	GLTextureBatcher::~GLTextureBatcher()
	{
		delete m_program;
		delete m_vBuffer;
		delete m_iBuffer;
	}

	void GLTextureBatcher::Begin(BatchSortMode mode)
	{
		m_sortMode = mode;
		m_BEFlag = true;
	}

	void GLTextureBatcher::Draw(Texture* texture, BatchInfo info)
	{
		if (!texture)
			return;

		if (m_textureCount >= MAX_BATCH_SIZE || m_texture && (m_texture != texture))
		{
			/*sort textures*/
			sort_textures();
			/*flush*/
			flush();
		}

		/*add texture to collection*/
		m_textures.push_back(info);
		m_textureCount++;

		/*cache texture*/
		m_texture = (GLTexture*)texture;

		/*if immediate mode, flush*/
		if (m_sortMode == BatchSortMode::IMMEDITATE)
			flush();
	}

	void GLTextureBatcher::End()
	{
		if (m_sortMode != BatchSortMode::IMMEDITATE) {
			/*sort textures*/
			sort_textures();

			/*flush*/
			flush();
		}

		m_BEFlag = false;
	}

	ErrCode GLTextureBatcher::init_shader_program()
	{
		/*vertex shader info*/
		ShaderInfo vshader_info;
		vshader_info.filePath = VTEXT("");
		vshader_info.raw = DEF_VERT_SHADER;
		vshader_info.type = ShaderType::VERTEX_SHADER;

		/*fragment shader info*/
		ShaderInfo fshader_info;
		fshader_info.filePath = VTEXT("");
		fshader_info.raw = DEF_FRAG_SHADER;
		fshader_info.type = ShaderType::FRAGMENT_SHADER;

		/*populate shader args*/
		ShaderArgs args;
		args[0] = vshader_info;
		args[1] = fshader_info;

		/*create shader program*/
		m_program = new GLShaderProgram(args);
		if (!m_program)
			return ErrCode::ERR_FAILURE;

		return ErrCode::ERR_SUCCESS;
	}

	void GLTextureBatcher::sort_textures()
	{
		switch (m_sortMode)
		{
		case BatchSortMode::BACK_TO_FRONT:
			/*sort back to front*/
			std::sort(m_textures.begin(),
				m_textures.end(), [](const BatchInfo x, const BatchInfo y)
			{
				return x.depth > y.depth;
			});
			break;

		case BatchSortMode::FRONT_TO_BACK:
			/*sort front to back*/
			std::sort(m_textures.begin(),
				      m_textures.end(), [](const BatchInfo x, const BatchInfo y)
			{
				return x.depth < y.depth;
			});
			break;
		}
	}

	void GLTextureBatcher::build_texture(BatchInfo info, size_t index)
	{
		/*cache alpha*/
		m_alpha = info.alpha;

		/*cache texture width and height*/
		const float tex_width = (float)m_texture->getWidth();
		const float tex_height = (float)m_texture->getHeight();
		const float inv_tex_width = 1.0f / tex_width;
		const float inv_tex_height = 1.0f / tex_height;

		//----------------------
		// x1 = x
		// y1 = y
		// x2 = x + width
		// y2 = y + height
		//
		//(x1,y1)-----------(x2,y1)
		// |                      |
		// |                      |
		// |                      |
		// |                      |
		// |                      |
		// |                      |
		//(x1,y2)-----------(x2,y2)


		/*store origin offset based on position*/
		const float worldOriginX = info.x + info.originX;
		const float worldOriginY = info.y + info.originY;

		/*create corner points (pre-transform)*/
		float fx = -info.originX;
		float fy = -info.originY;
		float fx2;
		float fy2;
		if (info.sW != 0 || info.sH != 0) {
			fx2 = info.sW - info.originX;
			fy2 = info.sH - info.originY;
		}
		else {
			fx2 = tex_width - info.originX;
			fy2 = tex_height - info.originY;
		}

		/*apply scale*/
		fx *= info.scaleX;
		fy *= info.scaleY;
		fx2 *= info.scaleX;
		fy2 *= info.scaleY;

		/*construct corners*/
		const float c1x = fx;
		const float c1y = fy;
		const float c2x = fx2;
		const float c2y = fy;
		const float c3x = fx;
		const float c3y = fy2;
		const float c4x = fx2;
		const float c4y = fy2;


		/*create temp vars for corner points to have rotation applied*/
		float x1;
		float y1;
		float x2;
		float y2;
		float x3;
		float y3;
		float x4;
		float y4;

		/*apply rotation*/
		if (info.rotation) {

			const float cos = glm::cos(info.rotation);
			const float sin = glm::sin(info.rotation);

			//To rotate a point around origin point
			//the solution follows the trigonometric function:
			//[x'] = [cos0 - sin0][x]
			//[y'] = [sin0 + cos0][y]
			//
			//So when expanded we are left with:
			//
			// x' = x * cos0 - y * sin0
			// y' = x * sin0 + y * cos0
			//

			x1 = cos * c1x - sin * c1y;
			y1 = sin * c1x + cos * c1y;
			x2 = cos * c2x - sin * c2y;
			y2 = sin * c2x + cos * c2y;
			x3 = cos * c3x - sin * c3y;
			y3 = sin * c3x + cos * c3y;
			x4 = cos * c4x - sin * c4y;
			y4 = sin * c4x + cos * c4y;
		}
		else { /*no rotation*/
			x1 = c1x;
			y1 = c1y;
			x2 = c2x;
			y2 = c2y;
			x3 = c3x;
			y3 = c3y;
			x4 = c4x;
			y4 = c4y;
		}

		/*add origin offset*/
		x1 += worldOriginX;
		y1 += worldOriginY;
		x2 += worldOriginX;
		y2 += worldOriginY;
		x3 += worldOriginX;
		y3 += worldOriginY;
		x4 += worldOriginX;
		y4 += worldOriginY;

		/*setup uv's appropriate to source rect*/
		float u;
		float v;
		float u2;
		float v2;

		Rect src_rect((int)info.sX, (int)info.sY, (int)info.sW, (int)info.sH);
		if (src_rect.HasValue()) {
			u = info.sX * inv_tex_width;
			v = info.sY * inv_tex_height;
			u2 = (info.sX + info.sW) * inv_tex_width;
			v2 = (info.sY + info.sH) * inv_tex_height;
		}
		else {
			u = 0.0f;
			v = 0.0f;
			u2 = 1.0f;
			v2 = 1.0f;
		}

		/*build vertices*/
		const std::array<Vertex2D, VERTS_PER_TEX> temp =
		{
			Vertex2D(x1, y1, info.r, info.g, info.b, info.a, u, v),
			Vertex2D(x2, y2, info.r, info.g, info.b, info.a, u2, v),
			Vertex2D(x3, y3, info.r, info.g, info.b, info.a, u, v2),
			Vertex2D(x4, y4, info.r, info.g, info.b, info.a, u2, v2)
		};

		/*add vertex information to buffer*/
		size_t offset = m_vBuffer->get_stride() * index * VERTS_PER_TEX;
		m_vBuffer->set(offset, VERTS_PER_TEX, temp.data());
 	}

	void GLTextureBatcher::render_textures()
	{
		/*bind buffers*/

		m_vBuffer->bind();
	  	m_iBuffer->bind();
		/*bind shader*/
		m_program->Bind();
		/*bind texture*/
		m_texture->Bind(GL_TEXTURE0);

		/*setup uniform variables*/
		GLuint projLoc;
//#if defined UNICODE && defined VIX_SYS_WINDOWS
//		UConverter cv;
//		const char* proj = cv.to_bytes(UNIFORM_PROJECTION).c_str();
//#else
//		const char* proj = UNIFORM_PROJECTION.c_str();
//#endif
		m_program->GetUniformLoc(SHADER_GLOBAL_PROJECTION, projLoc);
		GLuint alphaLoc;
		m_program->GetUniformLoc("gAlpha", alphaLoc);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera->Projection()));
		glUniform1f(alphaLoc, m_alpha);

		/*enable vertex attributes*/
		Vertex2D::Enable(true);

		/*render textures*/
		Vertex2D::Render(m_textureCount * INDICES_PER_TEX);

		/*disable vertex attributes*/
		Vertex2D::Enable(false);

		/*unbind buffers*/
		m_vBuffer->unbind();

		m_iBuffer->unbind();
		/*unbind shader*/
		m_program->Unbind();
		/*unbind texture*/
		m_texture->Unbind();

		m_textureCount = 0;

		m_textures.clear();

		m_texture = NULL;
	}

	void GLTextureBatcher::flush()
	{
		/*if no textures, return*/
		if (m_textureCount <= 0)
			return;

		/*build all textures in batched info list*/
		for (size_t i = 0; i < m_textureCount; i++) {
			BatchInfo info = m_textures[i];

			/*build texture*/
			build_texture(info, i);

		}


		/*render textures*/
		render_textures();
	}

}
