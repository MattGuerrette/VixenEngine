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

#include <vix_mesh.h>
#include <vix_debugutil.h>
#include <vix_model.h>

namespace Vixen {

	Mesh::Mesh(Model* parent, MeshInfo* info)
	{
		m_parent = parent;
		m_info = info;
		m_numVertices = info->NumVertices;
		m_numIndices = info->NumIndices;
		m_vBuffer = new VBuffers::PNTVBuffer(info->NumVertices);
		m_iBuffer = new GLIndexBuffer(info->NumIndices);
	}

	Mesh::~Mesh()
	{
		if(m_info)
			delete m_info;
	}

	const MeshInfo* const Mesh::GetInfo() const
	{
		return m_info;
	}

	void Mesh::Init()
	{
		m_vBuffer->set(0, m_numVertices, m_vertices.data());
		m_iBuffer->set(0, m_numIndices, m_indices.data());
	}

	void Mesh::AddVertex(float x, float y, float z,
						 float nx, float ny, float nz,
						 float u, float v,
						 float tx, float ty, float tz)
	{
		PositionNormalTexture vertex;
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
		vertex.nx = nx;
		vertex.ny = ny;
		vertex.nz = nz;
		vertex.u = u;
		vertex.v = v;
		vertex.tx = tx;
		vertex.ty = ty;
		vertex.tz = tz;

		m_vertices.push_back(vertex);
	}

	void Mesh::AddFace(unsigned short index01, unsigned short index02, unsigned short index03)
	{
		m_indices.push_back(index01);
		m_indices.push_back(index02);
		m_indices.push_back(index03);

	}

	void Mesh::applyTransform(GLCamera3D* camera)
	{
		GLuint projLoc;
		GLuint worldLoc;
		GLuint viewLoc;
		GLuint diffuseLoc;
		GLuint bumpLoc;


		m_parent->GetShader()->GetUniformLoc(SHADER_GLOBAL_PROJECTION, projLoc);
		m_parent->GetShader()->GetUniformLoc(SHADER_GLOBAL_VIEW, viewLoc);
		m_parent->GetShader()->GetUniformLoc(SHADER_GLOBAL_WORLD, worldLoc);
		m_parent->GetShader()->GetUniformLoc("gDiffuse", diffuseLoc);
		m_parent->GetShader()->GetUniformLoc("gBump", bumpLoc);

		m_parent->GetWorldMatrix() =
			glm::translate(Mat4(1.0f), m_parent->GetPosition()) *
			glm::rotate(Mat4(1.0f), m_parent->GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(Mat4(1.0f), m_parent->GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(Mat4(1.0f), m_parent->GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(Mat4(1.0f), m_parent->GetScale());

		/*apply value from camera*/
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(m_parent->GetWorldMatrix()));
		m_parent->GetTexture()->Bind(GL_TEXTURE0);
		//m_parent->GetBump()->Bind(GL_TEXTURE1);
		glUniform1i(diffuseLoc, 0);
		//glUniform1i(bumpLoc, 1);
	}

	void Mesh::Render(GLCamera3D* camera)
	{
		m_parent->GetShader()->Bind();
		m_vBuffer->bind();
		m_iBuffer->bind();
		/*m_parent->GetTexture()->Bind(GL_TEXTURE0);
		m_parent->GetBump()->Bind(GL_TEXTURE1);*/

		applyTransform(camera);

		PositionNormalTexture::Enable(true);
		PositionNormalTexture::RenderElements(m_numIndices, GL_TRIANGLES);
		PositionNormalTexture::Enable(false);

		m_parent->GetShader()->Unbind();
		m_vBuffer->unbind();
		m_iBuffer->unbind();
		m_parent->GetTexture()->Unbind();
		//m_parent->GetBump()->Unbind();
	}

}
