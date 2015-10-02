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