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

#ifndef VIX_RECTANGLE_H
#define VIX_RECTANGLE_H

#include <vix_platform.h>
#include <vix_stringutil.h>

namespace Vixen {

	class   Rectangle;
	typedef Rectangle Rect;

	class VIX_API Rectangle
	{
	public:
		int x;
		int y;
		int w;
		int h;
	public:
		inline Rectangle()
			: x(0), y(0), w(0), h(0)
		{

		}

		inline Rectangle(int _x, int _y, int _w, int _h)
			: x(_x), y(_y), w(_w), h(_h)
		{

		}

		/*Properties*/
		inline int Left()     const { return x; }
		inline int Right()    const { return x + w; }
		inline int Top()      const { return y; }
		inline int Bottom()   const { return y + h; }

		/*Functions*/

		bool HasValue();

		bool Contains(int _x, int _y);

		bool Intersects(const Rect& r);


		/*operators*/

		inline bool operator== (const Rectangle& rhs)
		{
			return (x == rhs.x &&
				    y == rhs.y &&
				    w == rhs.w &&
				    h == rhs.h);
		}

		inline bool operator!= (const Rectangle& rhs)
		{
			return !(*this == rhs);
		}

		inline VIX_API friend UOStream& operator <<
			(UOStream& o, const Rect& r)
		{
			o << "Rectangle [ "
				<< "X=" << r.x << " "
				<< "Y=" << r.y << " "
				<< "W=" << r.w << " "
				<< "H=" << r.h
				<< " ]";
			return o;
		}

		static const Rectangle EMPTY;
	};

}

#endif
