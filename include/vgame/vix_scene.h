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

#ifndef VIX_SCENE_H
#define VIX_SCENE_H

#include <vix_containers.h>
#include <vix_gameobject.h>
#include <vix_component.h>
#include <vix_tinyxml.h>
#include <vix_camera2d.h>

namespace Vixen {
	class VIX_API Scene
	{
	public:
		Scene();
		~Scene();

		/*Update Scene*/
		void Update();

		/*Render Scene*/
		void Render();

		/*Adds Object with ID to Scene*/
		void AddSceneObject(GameObject* object);
		void RemoveSceneObject(GameObject* object);
	
		GameObject* QueryObject(std::string name);

		void SetPaused(bool paused);
		void SetHidden(bool hidden);
		
		bool IsPaused();
		bool IsHidden();
		

		/*SETTER FUNCTIONS*/
		void SetID(std::string id);

		void SetMainCamera(ICamera3D* camera);

		/*GETTER FUNCTIONS*/
		const std::string& GetID();				//returns ID of scene

	private:
		uint32_t						m_order;
		std::string						m_id;				//scene ID
		bool							m_paused;
		bool							m_hidden;
		std::vector<GameObject*>		m_topLevelObjects;
		ICamera3D*                      m_mainCamera;
        ICamera2D*                      m_uiCamera;

	public:
		static Scene*                   Deserialize(File* file);

    private:
		static GameObject*              ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element);
		static Transform*               ParseTransform(const tinyxml2::XMLElement * element);
		static std::vector<IComponent*>	ParseComponents(Scene* scene, const tinyxml2::XMLElement* element);
		static IComponent*	            ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement* element);
		static IComponent*              ParseLightComponent(const tinyxml2::XMLElement* element);
		static IComponent*              ParseLuaScriptComponent(const tinyxml2::XMLElement* element);
        static IComponent*              ParseUITextComponent(const tinyxml2::XMLElement* element);
		static IComponent*				ParseModelComponent(const tinyxml2::XMLElement* element);
	};
}
#endif