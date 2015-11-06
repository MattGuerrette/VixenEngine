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

#ifndef VIX_TRANSFORM_H
#define VIX_TRANSFORM_H

#include <vix_platform.h>
#include <vix_vector3.h>

namespace Vixen {

	class GameObject;

    class VIX_API Transform
    {
    public:
        Transform();
        Transform(float posX, float posY, float posZ,
                  float rotX, float rotY, float rotZ,
                  float scaleX, float scaleY, float scaleZ);
        Transform(Vector3 position, Vector3 rotation, Vector3 scale);


		MATRIX* GetWorldMatrix();
		MATRIX* GetLocalMatrix();

		void SetDirty();

        void RotateX(float val);
        void RotateY(float val);
        void RotateZ(float val);
        void TranslateX(float val);
        void TranslateY(float val);
        void TranslateZ(float val);
		void Translate(Vector3 val);
		//void Translate(float x, float y, float z);

		Vector3 GetPosition();
		Vector3 GetWorldPosition();
		Vector3 GetRotation();
		Vector3 GetScale();
		Vector3 GetForward();
		Vector3 GetUp();
		Vector3 GetRight();

        Vector3* GetRotationRef();

		void SetPosition(Vector3 val);
		void SetRotation(Vector3 val);
		void SetScale(Vector3 val);

        float X() const;
        float Y() const;
        float Z() const;
        float RotX() const;
        float RotY() const;
        float RotZ() const;
        float ScaleX() const;
        float ScaleY() const;
        float ScaleZ() const;

		void DebugPrint();

		void AddChildTransform(Transform* transform);
		void RemoveChildTransform(Transform* transform);

        bool IsDirty();

    private:
        Vector3 m_position;
        Vector3 m_rotation;
        Vector3 m_scale;

		Vector3 m_worldPosition;


		Vector3 m_forward;
		Vector3 m_up;
		Vector3 m_right;

		MATRIX  m_world;
		MATRIX  m_local;

		bool	m_localDirty;
		bool    m_worldDirty;
		bool    m_test;

		std::vector<Transform*> m_childTransforms;
		Transform*              m_parent;
    };

}

#endif
