#include <vix_scene.h>

namespace Vixen {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::Serialize(XMLDOC& doc)
	{
		using namespace tinyxml2;

#ifdef VIX_SYS_WINDOWS
		UConverter cv;
		std::string id = cv.to_bytes(m_id.c_str());
#else
		UString id = m_id;
#endif
		XMLDeclaration* decl = doc.NewDeclaration();
		XMLElement* newElement = doc.NewElement("scene");
		newElement->SetAttribute("id", id.c_str());
		doc.InsertEndChild(decl);
		doc.InsertEndChild(newElement);

		/*SERIALIZE ALL SCENE OBJECTS*/
		//....
		//....
		for(auto& obj : m_sceneObjects)
			obj.second->Serialize(doc);
	}

	void Scene::Deserialize(XMLDOC& doc)
	{

	}

	void Scene::AddSceneObject(UString id, GameObject* object)
	{
		ObjectList::iterator it = m_sceneObjects.find(id);
		if(it == m_sceneObjects.end()) {
			object->SetID(id);
			m_sceneObjects[id] =  object;
		}
		else {
			USStream ss;
			ss << "Object: " << id << " already exists in scene";
			DebugPrintF(ss.str().c_str());
		}
	}

	void Scene::RemoveSceneObject(UString id)
	{
		m_sceneObjects.erase(id);
	}

	void Scene::Update(float dt)
	{
		//update all scene objects
		for(auto& object: m_sceneObjects)
			object.second->Update(dt);
	}

	void Scene::Render(GLRenderer* renderer, float dt)
	{
		//render all scene objects
		for(auto& object : m_sceneObjects)
			object.second->Render(renderer, dt);
	}


	/*SETTER FUNCTIONS*/

	void Scene::SetID(UString id)
	{
		m_id = id;
	}

	void Scene::SetPath(UString path)
	{
		m_filePath = path;
	}

	/*GETTER FUNCTIONS*/
	const UString& Scene::GetID()
	{
		return m_id;
	}

	const UString& Scene::GetFilePath()
	{
		return m_filePath;
	}
}