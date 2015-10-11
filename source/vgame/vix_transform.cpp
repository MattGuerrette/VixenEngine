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

#include <vix_transform.h>
#include <vix_mathfunctions.h>


namespace Vixen {

    Transform::Transform()
    {
        m_position = Vector3(0.0f, 0.0f, 0.0f);
        m_rotation = Vector3(0.0f, 0.0f, 0.0f);
        m_scale = Vector3(1.0f, 1.0f, 1.0f);

		m_forward = Vector3(0.0f, 0.0f, 1.0f);
		m_up = Vector3(0.0f, 1.0f, 0.0f);
		m_right = Vector3(1.0f, 0.0f, 0.0f);



		m_parent = NULL;
		SetDirty();
    }

    Transform::Transform(float posX, float posY, float posZ,
                         float rotX, float rotY, float rotZ,
                         float scaleX, float scaleY, float scaleZ)
    {
        m_position = Vector3(posX, posY, posZ);
        m_rotation = Vector3(rotX, rotY, rotZ);
        m_scale = Vector3(scaleX, scaleY, scaleZ);

		m_forward = Vector3(0.0f, 0.0f, 1.0f);
		m_up = Vector3(0.0f, 1.0f, 0.0f);
		m_right = Vector3(1.0f, 0.0f, 0.0f);



		m_parent = NULL;
		SetDirty();
    }

    Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
    {
        m_position = position;
        m_rotation = rotation;
        m_scale = scale;

		m_forward = Vector3(0.0f, 0.0f, 1.0f);
		m_up = Vector3(0.0f, 1.0f, 0.0f);
		m_right = Vector3(1.0f, 0.0f, 0.0f);



		m_parent = NULL;
		SetDirty();
    }

	void Transform::SetDirty()
	{
		if (!m_worldDirty) {
			m_worldDirty = true;

			for (int i = 0; i < m_childTransforms.size(); i++)
			{
				Transform* _transform = m_childTransforms[i];
				_transform->SetDirty();
			}
		}

		if(!m_localDirty)
			m_localDirty = true;
	}

	void Transform::AddChildTransform(Transform* transform)
	{
		m_childTransforms.push_back(transform);
		transform->m_parent = this;
		transform->SetDirty();
	}

    void Transform::TranslateX(float val)
    {
		SetDirty();
        m_position.x += val;
    }

    void Transform::TranslateY(float val)
    {
		SetDirty();
        m_position.y += val;
    }

    void Transform::TranslateZ(float val)
    {
		SetDirty();
        m_position.z += val;
    }

	void Transform::Translate(Vector3 val)
	{
		SetDirty();
		m_position.x += val.x;
		m_position.y += val.y;
		m_position.z += val.z;
	}

	/*void Transform::Translate(float x, float y, float z)
	{
		SetDirty();
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
	}*/

	Vector3 Transform::GetPosition()
	{
		this->GetWorldMatrix();
		return m_position;
	}

	Vector3 Transform::GetWorldPosition()
	{
		this->GetWorldMatrix();
		return m_worldPosition;
	}

	Vector3 Transform::GetRotation()
	{
		this->GetWorldMatrix();
		return m_rotation;
	}

	Vector3 Transform::GetScale()
	{
		this->GetWorldMatrix();
		return m_scale;
	}

	Vector3 Transform::GetForward()
	{
		this->GetWorldMatrix();
		return m_forward;
	}

	Vector3 Transform::GetUp()
	{
		this->GetWorldMatrix();
		return m_up;
	}

	Vector3 Transform::GetRight()
	{
		this->GetWorldMatrix();
		return m_right;
	}

	void Transform::SetPosition(Vector3 val)
	{
		SetDirty();
		m_position = val;
	}

	void Transform::SetRotation(Vector3 val)
	{
		SetDirty();
		m_rotation = val;
	}

	void Transform::SetScale(Vector3 val)
	{
		SetDirty();
		m_scale = val;
	}

    void Transform::RotateX(float val)
    {
		SetDirty();
        m_rotation.x += val;
    }

    void Transform::RotateY(float val)
    {
		SetDirty();
        m_rotation.y += val;
    }

    void Transform::RotateZ(float val)
    {
		SetDirty();
        m_rotation.z += val;
    }

    Vector3* Transform::GetRotationRef()
    {
        return &m_rotation;
    }

    float Transform::X() const
    {
        return m_position.x;
    }

    float Transform::Y() const
    {
        return m_position.y;
    }

    float Transform::Z() const
    {
        return m_position.z;
    }

    float Transform::RotX() const
    {
        return m_rotation.x;
    }

    float Transform::RotY() const
    {
        return m_rotation.y;
    }

    float Transform::RotZ() const
    {
        return m_rotation.z;
    }

    float Transform::ScaleX() const
    {
        return m_scale.x;
    }

    float Transform::ScaleY() const
    {
        return m_scale.y;
    }

    float Transform::ScaleZ() const
    {
        return m_scale.z;
    }

    bool Transform::IsDirty()
    {
        return m_worldDirty || m_localDirty;
    }

	MATRIX* Transform::GetWorldMatrix()
	{

		if (m_worldDirty) {
			m_worldDirty = false;
			if (m_parent)
				m_world = (*GetLocalMatrix()) * (*m_parent->GetWorldMatrix());
			else
				m_world = *GetLocalMatrix();


			m_worldPosition = MathFunctions::TransformVector(Vector3(0, 0, 0), m_world);

			//recalculate basis vectors (right, forward, up)
			m_forward = MathFunctions::TransformVectorRotationScale(Vector3(0, 0, 1), m_world);
			m_forward.normalise();

			m_up = MathFunctions::TransformVectorRotationScale(Vector3(0, 1, 0), m_world);
			m_up.normalise();

			m_right = m_up.Cross(m_forward);


		}

		return &m_world;
	}

	MATRIX* Transform::GetLocalMatrix()
	{
		if (m_localDirty) {
			m_local = MathFunctions::MatrixScaling(m_scale) *
				MathFunctions::MatrixRotation(m_rotation) *
				MathFunctions::MatrixTranslation(m_position);
			m_localDirty = false;
		}

		return &m_local;
	}

	void Transform::DebugPrint()
	{
		DebugPrintF(VTEXT("Transform [X: %.3f, Y: %.3f, Z: %.3f]\n"), m_position.x, m_position.y, m_position.z);
	}
}
