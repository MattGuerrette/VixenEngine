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
