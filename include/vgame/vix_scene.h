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
		void AddCamera(ICamera3D* camera);
		void RemoveCamera(ICamera3D* camera);

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
		std::vector<ICamera3D*>			m_cameras;

		ICamera3D*                      m_mainCamera;

        ICamera2D*                      m_uiCamera;

        friend class SceneManager;

	public:
		static Scene*                   Deserialize(File* file);

    private:
		static GameObject*              ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element);
		static Transform*               ParseTransform(const tinyxml2::XMLElement * element);

		static std::vector<Component*>	ParseComponents(Scene* scene, const tinyxml2::XMLElement* element);
		static Component*	            ParseCameraComponent(Scene* scene, const tinyxml2::XMLElement* element);
		static Component*				ParseLightComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseLuaScriptComponent(const tinyxml2::XMLElement* element);
        static Component*				ParseUITextComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseModelComponent(const tinyxml2::XMLElement* element);
		static Component*				ParseRigidBodyComponent(const tinyxml2::XMLElement* element);
	};
}
#endif
