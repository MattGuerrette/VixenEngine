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
		void SetFileName(std::string name);
		void SetMainCamera(ICamera3D* camera);

		/*GETTER FUNCTIONS*/
		const std::string& GetID();				//returns ID of scene
		const std::string& GetFileName();
	private:
		uint32_t						m_order;
		std::string						m_id;				//scene ID
		std::string						m_fileName;
		bool							m_paused;
		bool							m_hidden;
		std::vector<GameObject*>		m_topLevelObjects;
		ICamera3D*                      m_mainCamera;
        ICamera2D*                      m_uiCamera;

	public:
<<<<<<< HEAD
		static Scene* Deserialize(File* file);
		static GameObject* ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element);
		static Transform* ParseTransform(const tinyxml2::XMLElement * element);
		static std::vector<IComponent*>	ParseComponents(Scene* scene, const tinyxml2::XMLElement* element);
		static CameraComponent*	ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement* element);
		static LightComponent* ParseLightComponent(const tinyxml2::XMLElement* element);
		//static LuaScript* ParseLuaScriptComponent(const tinyxml2::XMLElement* element);
=======
		static Scene*                   Deserialize(File* file);

    private:
		static GameObject*              ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element);
		static Transform*               ParseTransform(const tinyxml2::XMLElement * element);
		static std::vector<Component*>	ParseComponents(Scene* scene, const tinyxml2::XMLElement* element);
		static Component*	            ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement* element);
		static Component*              ParseLightComponent(const tinyxml2::XMLElement* element);
		static Component*              ParseLuaScriptComponent(const tinyxml2::XMLElement* element);
        static Component*              ParseUITextComponent(const tinyxml2::XMLElement* element);
>>>>>>> 5d61730afc80281f2da012a8e50084e490f8a879
	};
}
#endif
