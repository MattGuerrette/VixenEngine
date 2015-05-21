#ifndef VIX_SCENE_H
#define VIX_SCENE_H

#include <vix_platform.h>
#include <vix_gameobject.h>
#include <vix_tinyxml.h>
#include <vector>
#include <map>

namespace Vixen {


	class VIX_API Scene
	{
		typedef std::map<UString, GameObject*> ObjectList;
	public:
		Scene();

		~Scene();

		/*Update Scene*/
		void Update(float dt);
		/*RenderScene*/
		void Render(GLRenderer* renderer, float dt);

		/*Adds Object with ID to Scene*/
		void AddSceneObject(UString id, GameObject* object);

		/*Removes Object with ID from Scene*/
		void RemoveSceneObject(UString id);

		/*Writes Scene to XML document file*/
		void Serialize(XMLDOC& doc);

		/*Reads Scene from XML document file*/
		void Deserialize(XMLDOC& doc);


		/*SETTER FUNCTIONS*/
		void SetID(UString id);
		void SetPath(UString path);

		/*GETTER FUNCTIONS*/
		const UString& GetID();				//returns ID of scene
		const UString& GetFilePath();		//returns path to scene file (.vsf)

	private:
		UString      m_id;				//scene ID
		UString      m_filePath;		//scene file path (path to .vsf)
		ObjectList   m_sceneObjects;    //collection of scene objects
	};

}

#endif