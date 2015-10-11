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

#ifndef VIX_OBJECTMANAGER_H
#define VIX_OBJECTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_gameobject.h>

namespace Vixen {

	class VIX_API ObjectManager : public Singleton<ObjectManager>
	{
		class ObjectMap
		{
			static const int INIT_SIZE = 1;
		public:
			ObjectMap();

			~ObjectMap();

			void		InsertObject(GameObject* object);

			GameObject* AccessObject(uint32_t id);

			void        DestroyObject(uint32_t id);

		private:
			void Resize();

		private:
			uint32_t				m_count;
			uint32_t				m_size;
			uint32_t                m_currentIndex;
			GameObject**			m_data;
			std::queue<uint32_t>	m_openIDs;

		};

	public:

		static bool			Initialize();

		static void			DeInitialize();

		static void			MapSceneObject(GameObject* object);

		static GameObject*	AccessSceneObject(uint32_t id);

		static void			DestroyGameObject(GameObject* object);

		static void			DestroySceneObject(uint32_t id);

	private:
		ObjectMap*  m_objects;
	};

}

#endif
