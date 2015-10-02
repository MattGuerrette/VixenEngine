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
