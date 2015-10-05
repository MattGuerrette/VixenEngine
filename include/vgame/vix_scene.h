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

#include <vix_platform.h>
#include <vix_gameobject.h>
#include <vix_tinyxml.h>
#include <vix_containers.h>

namespace Vixen {

	class VIX_API Scene
	{
		

	public:
		Scene();

		~Scene();

		/*Update Scene*/
		void Update(float dt);

        /*Render Scene*/
        void Render(float dt, float totalTime);

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
        static Scene*		Deserialize(File* file);
		static GameObject*	ParseGameObject(Scene* scene, const tinyxml2::XMLElement* element);
	};

}

#endif