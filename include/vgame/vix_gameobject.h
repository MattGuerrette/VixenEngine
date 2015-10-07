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

#ifndef VIX_GAMEOBJECT_H
#define VIX_GAMEOBJECT_H

#include <vix_platform.h>
#include <vix_transform.h>
#include <vix_model.h>
#include <vix_camera3d.h>
#include <vix_component.h>
#include <vix_containers.h>

namespace Vixen {


	class VIX_API GameObject
	{
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

		void Update(float dt);
		void Render(float dt, ICamera3D* camera);
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