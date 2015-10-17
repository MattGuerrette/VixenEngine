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
