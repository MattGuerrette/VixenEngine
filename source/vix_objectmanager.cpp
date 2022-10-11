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

#include <vix_objectmanager.h>
#include <vix_scenemanager.h>

namespace Vixen {

	/////////////////////////////////////////////////
	// ObjectManager::ObjectMap implementation
	/////////////////////////////////////////////////

	ObjectManager::ObjectMap::ObjectMap()
	{
		m_data = new GameObject*[ObjectManager::ObjectMap::INIT_SIZE]{ 0 };
		m_size = ObjectManager::ObjectMap::INIT_SIZE;
		m_count = 0;
		m_currentIndex = 0;
	}

	ObjectManager::ObjectMap::~ObjectMap()
	{
		delete[] m_data;
	}


	void ObjectManager::ObjectMap::InsertObject(GameObject* object)
	{
		uint32_t _id = m_count;

		m_count++;

		Resize();

		if (m_openIDs.size() > 0) {
			m_currentIndex = m_openIDs.front();
			m_openIDs.pop();

			_id = m_currentIndex;
		}

		m_data[_id] = object;
		object->SetID(_id);
	}

	GameObject* ObjectManager::ObjectMap::AccessObject(uint32_t id)
	{
		if (id < m_size)
			return m_data[id];
		else
			return NULL;
	}

	void ObjectManager::ObjectMap::DestroyObject(uint32_t id)
	{
		if (id < m_size)
		{
			if (m_data[id]) {
				m_count--;

				delete m_data[id];
				m_data[id] = nullptr;
				m_openIDs.emplace(id);
			}

		}
	}

	void ObjectManager::ObjectMap::Resize()
	{
		if (m_count > m_size) {
			//need to allocate more space and copy
			uint32_t newMax = m_size * 2;
			GameObject** temp = new GameObject*[newMax] {0};

			#ifdef VIX_SYS_WINDOWS
				memcpy_s(temp, newMax * sizeof(GameObject*), m_data, m_size * sizeof(GameObject*));
			#else
				memcpy(temp, m_data, m_size * sizeof(GameObject*));
			#endif

			delete[] m_data;

			m_data = temp;

			m_size = newMax;
		}
	}

	///////////////////////////////////////////////////////////
	// ObjectManager implementation
	///////////////////////////////////////////////////////////

	bool ObjectManager::Initialize()
	{
		ObjectManager::instance().m_objects = new ObjectMap;

		return true;
	}

	void ObjectManager::DeInitialize()
	{
		delete ObjectManager::instance().m_objects;
	}

	void ObjectManager::MapSceneObject(GameObject* object)
	{
		ObjectManager& _manager = ObjectManager::instance();

		_manager.m_objects->InsertObject(object);
	}

	GameObject* ObjectManager::AccessSceneObject(uint32_t id)
	{
		ObjectManager& _manager = ObjectManager::instance();

		return _manager.m_objects->AccessObject(id);
	}

	void ObjectManager::DestroyGameObject(GameObject * object)
	{
		ObjectManager::instance().m_objects->DestroyObject(object->GetID());
	}

	void ObjectManager::DestroySceneObject(uint32_t id)
	{
		ObjectManager& _manager = ObjectManager::instance();

		_manager.m_objects->DestroyObject(id);
	}
}
