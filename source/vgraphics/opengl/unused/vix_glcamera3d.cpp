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

#include <vix_glcamera3d.h>

namespace Vixen {

	GLCamera3D::GLCamera3D()
	{
		  m_aspect = 0.0f;
		  m_fov = 0.0f;
		  m_znear = 0.0f;
		  m_zfar = 1000.0f;
		  m_position = Vec3(0.0f);
		  m_front = Vec3(0.0f, 0.0f, -1.0f);
		  m_up = Vec3(0.0f, 1.0f, 0.0f);
		  m_worldUp = Vec3(0.0f, 1.0f, 0.0f);
		  m_yaw = YAW;
		  m_pitch = PITCH;
		  m_speed = 10.0f;
	}

	GLCamera3D::GLCamera3D(C3D_TYPE type)
	{
		  m_aspect = 0.0f;
		  m_fov = 0.0f;
		  m_znear = 0.0f;
		  m_zfar = 1000.0f;
		  m_position = Vec3(0.0f);
		  m_front = Vec3(0.0f, 0.0f, -1.0f);
		  m_up = Vec3(0.0f, 1.0f, 0.0f);
		  m_worldUp = Vec3(0.0f, 1.0f, 0.0f);
		  m_yaw = YAW;
		  m_pitch = PITCH;
		  m_speed = 10.0f;
		  m_type = type;
	}

	void GLCamera3D::SetType(C3D_TYPE type)
	{
		m_type = type;
	}

	C3D_TYPE GLCamera3D::GetType()
	{
		return m_type;
	}

	void GLCamera3D::SetPerspective(float aspect, float fov, float znear, float zfar)
	{
		/*should probably check for stupid fov ranges*/
		m_aspect = aspect;
		m_fov = fov;
		m_znear = znear;
		m_zfar = zfar;
		m_projection = glm::perspective(m_fov, m_aspect, m_znear, m_zfar);
	}

	void GLCamera3D::SetView(const Vec3& pos, const Vec3& target, const Vec3& up)
	{
		m_view = glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void GLCamera3D::SetPosition(const Vec3& pos)
	{
		m_position = pos;
		SetView(m_position, m_position + m_front, m_up);
	}

	void GLCamera3D::Move(C3D_DIRECTION cam_dir)
	{
		switch (cam_dir)
		{
		case Vixen::C3D_DIRECTION::UP:
			m_moveDir = Vec3(0.0f, 1.0f, 0.0f);
			break;
		case Vixen::C3D_DIRECTION::DOWN:
			m_moveDir = Vec3(0.0f, -1.0f, 0.0f);
			break;
		case Vixen::C3D_DIRECTION::LEFT:
			m_moveDir = -glm::normalize(glm::cross(m_front, m_up));
			break;
		case Vixen::C3D_DIRECTION::RIGHT:
			m_moveDir = glm::normalize(glm::cross(m_front, m_up));
			break;
		case Vixen::C3D_DIRECTION::FORWARD:
			m_moveDir = m_front;
			break;
		case Vixen::C3D_DIRECTION::BACKWARD:
			m_moveDir = -m_front;
			break;
		default:
			break;
		}

		if(m_type == C3D_TYPE::FIRST_PERSON)
			m_moveDir.y = 0.0f;
	}

	const Vec3& GLCamera3D::Position() const
	{
		return m_position;
	}

	const Mat4& GLCamera3D::Projection() const
	{
		return m_projection;
	}

	const Mat4& GLCamera3D::View() const
	{
		return m_view;
	}

	const Vec3& GLCamera3D::Forward() const
	{
		return m_front;
	}


	void GLCamera3D::RotateY(float dt)
	{
		m_yaw += dt;
		if(m_yaw > 360.0f || m_yaw < -360.0f)
			m_yaw = 0.0f;
	}

	void GLCamera3D::RotateX(float dt)
	{
		m_pitch += dt;
		if (this->m_pitch > 89.0f)
            this->m_pitch = 89.0f;
        if (this->m_pitch < -89.0f)
            this->m_pitch = -89.0f;
	}

	float GLCamera3D::Yaw()
	{
		return m_yaw;
	}

	float GLCamera3D::Pitch()
	{
		return m_pitch;
	}

	void GLCamera3D::SetSpeed(float speed)
	{
		m_speed = speed;
	}

	void GLCamera3D::Update(float dt)
	{
		m_position += m_moveDir * dt * m_speed;

		 // Calculate the new Front vector
        glm::vec3 front;
        m_front.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
        m_front.y = sin(glm::radians(this->m_pitch));
        m_front.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
        this->m_front = glm::normalize(m_front);
        // Also re-calculate the m_right and Up vector
		this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        this->m_up    = glm::normalize(glm::cross(this->m_right, this->m_front));

		SetView(m_position, m_position + m_front, m_up);

		m_moveDir = Vec3(0.0f);
	}
}
