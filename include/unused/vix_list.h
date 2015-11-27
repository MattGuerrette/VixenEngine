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
