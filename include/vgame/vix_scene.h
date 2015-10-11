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
#include <vix_tinyxml.h>

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
		void QueObjectSpawn(GameObject* object);
		void QueObjectDestroy(GameObject* object);
		GameObject* QueryObject(std::string name);

		/*Removes Object with ID from Scene*/
		void DestroyObjects();

		void SetPaused(bool paused);

		/*SETTER FUNCTIONS*/
		void SetID(UString id);

		/*GETTER FUNCTIONS*/
		const UString& GetID();				//returns ID of scene

	private:
		UString							m_id;				//scene ID
		bool							m_paused;
		std::vector<GameObject*>		m_topLevelObjects;
		std::vector<GameObject*>        m_objectsToAdd;
		std::vector<GameObject*>        m_objectsToRemove;
		ICamera3D*                      m_mainCamera;

	public:
		static Scene* Deserialize(File* file);
		static GameObject* ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element);
		static Transform* ParseTransform(const tinyxml2::XMLElement * element);
		static std::vector<IComponent*>	ParseComponents(Scene* scene, const tinyxml2::XMLElement* element);
		static CameraComponent*	ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement* element);
		static LightComponent* ParseLightComponent(const tinyxml2::XMLElement* element);
		static LuaScript* ParseLuaScriptComponent(const tinyxml2::XMLElement* element);
	};
}
#endif
