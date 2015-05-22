#ifndef VIX_LIST_H
#define VIX_LIST_H

#include <vix_platform.h>
#include <vix_typedefs.h>
#include <cassert>

namespace Vixen {

	template<typename T>
	class VIX_API List
	{
		/*Node definition*/
		class Node
		{
		private:
			T*		data;
			Node*	prev;
			Node*   next;

			void ClearData() {
				data = NULL;
			}
			void ClearLinks() {
				prev = NULL;
				next = NULL;
			}
		
			friend class List<T>;

		private:
			/*Constructor*/
			Node();

			/*Returns the next node*/
			Node* GetNext() {
				return next;
			}

			/*Returns the previous node*/
			Node* GetPrev() {
				return prev;
			}

			/*Returns the data*/
			T*    GetData() {
				return data;
			}

			bool  IsNull() {
				if(!data) {
					assert(!next)
					assert(!prev)

					return true;
				}
				else
					return false;
			}
		};

	public:
		
		/*Iterator definition*/
		class Iterator
		{
			const List<T>* list;
			Node*          current;
			int32_t        position;
		};
	};

}

#endif