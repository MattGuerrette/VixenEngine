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
#include <vix_containers.h>
#include <vix_component.h>
#include <vix_components.h>
#include <vix_transform.h>
#include <vix_components.h>

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
		
		~GameObject();

		Transform* GetTransform();
		Transform& GetTransformRef();

		void AddComponent(Component* component);
		void AddChild(GameObject* gameObject);
		void RemoveChild(GameObject* gameObject);

		void Update();
		void Render(ICamera3D* camera);
		bool GetEnabled();
		void SetEnabled(bool state, bool recursive);
		bool IsMarkedForDestroy();
        bool IsMarkedForLateRender();

        void MarkForLateRender();

		void Delete();

		uint32_t    GetID();
		void        SetID(uint32_t id);

		std::string GetName();
		void        SetName(UString id);

		GameObject* GetParent();

		GameObject* GetChild(int index);


		Camera3DComponent* Get3DCameraComponent();

	private:
		bool						m_enabled;
		bool						m_markedForDestroy;
        bool                        m_markedForLateRender;
		uint32_t                    m_id;
		UString                     m_name;
		Transform*					m_transform;

		std::vector<Component*>		m_components;
		std::vector<GameObject*>    m_children;
		GameObject*					m_parent;


    public:
        template <typename T>
        T* GetComponent();
	};



    //////////////////////////////////////////////////////////////////////
    //  TEMPLATE SPECIALIZATIONS
    //////////////////////////////////////////////////////////////////////

    template <>
    inline UIText* GameObject::GetComponent()
    {
        uint32_t numComponents = m_components.size();
        for (uint32_t i = 0; i < numComponents; i++)
        {
            UIText* _text = dynamic_cast<UIText*>(m_components[i]);
            if (_text)
                return _text;
        }

        return NULL;
    }

    template <>
    inline ModelComponent* GameObject::GetComponent()
    {
        uint32_t numComponents = m_components.size();
        for (uint32_t i = 0; i < numComponents; i++)
        {
            ModelComponent* _model = dynamic_cast<ModelComponent*>(m_components[i]);
            if (_model)
                return _model;
        }

        return NULL;
    }

    template <>
    inline Camera3DComponent* GameObject::GetComponent()
    {
        uint32_t numComponents = m_components.size();
        for (uint32_t i = 0; i < numComponents; i++)
        {
            Camera3DComponent* _camera = dynamic_cast<Camera3DComponent*>(m_components[i]);
            if (_camera)
                return _camera;
        }

        return NULL;
    }
}

#endif