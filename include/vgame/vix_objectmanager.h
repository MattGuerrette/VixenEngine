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
