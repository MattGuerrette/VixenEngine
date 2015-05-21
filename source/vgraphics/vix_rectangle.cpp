/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

#include <vix_rectangle.h>

namespace Vixen {

	const Rectangle Rectangle::EMPTY(0, 0, 0, 0);

	/*Checks whether given point is bounded by Rectangle*/
	bool Rectangle::Contains(int _x, int _y)
	{
		return ((((this->x <= _x) && (_x < (this->x + this->w)))
			   && (this->y <= _y)) && (_y < (this->y + this->h)));
	}

	/*Checks whether Rectangle has any value*/
	bool Rectangle::HasValue()
	{
		return x != 0 || y != 0 || w != 0 || h != 0;
	}

	/*Checks whether Rectangle intersects with another Rectangle*/
	bool Rectangle::Intersects(const Rect& r)
	{
		return !( r.Left() > Right()
			||  r.Right() < Left()
			||  r.Top() > Bottom()
			||  r.Bottom() < Top());
	}

}
