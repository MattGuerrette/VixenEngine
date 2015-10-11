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

#ifndef VIX_GAMEOBJECT_H
#define VIX_GAMEOBJECT_H

#include <vix_platform.h>
#include <vix_containers.h>
#include <vix_components.h>
#include <vix_model.h>

namespace Vixen {


	class VIX_API GameObject
	{
    public:
        static void         _TranslateZ(float val);
        static Transform*   _GetTransform();
        static void         _SetTransformPosition(Vector3 v);
        static Vector3      _GetTransformPosition();
        static float        _GetTransformZ();
        static GameObject*  _GetActiveObject();
        static GameObject*  s_ActiveObject;
	public:
		GameObject();
		GameObject(Transform* transform);
		GameObject(Transform* transform, IModel* model);

		~GameObject();

		void SetModel(IModel* model);

		Transform* GetTransform();
		Transform& GetTransformRef();

		void AddComponent(IComponent* component);
		void AddChild(GameObject* gameObject);

		void Update();
		void Render(ICamera3D* camera);
		bool GetEnabled();
		void SetEnabled(bool state, bool recursive);

		void Delete();

		uint32_t    GetID();
		void        SetID(uint32_t id);

		std::string GetName();
		void        SetName(UString id);

		GameObject* GetParent();

		GameObject* GetChild(int index);


	private:
		bool						m_enabled;

		uint32_t                    m_id;
		UString                     m_name;
		Transform*					m_transform;
		IModel*						m_model;
		std::vector<IComponent*>	m_components;

		std::vector<GameObject*>    m_children;
		GameObject*					m_parent;

	};

}

#endif
