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
