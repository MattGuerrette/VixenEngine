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

#ifndef VIX_SPRITEBATCHER_H
#define VIX_SPRITEBATCHER_H

namespace Vixen {

    enum class BatchSortMode
    {
        IMMEDITATE,
        DEFERED,
        BACK_TO_FRONT,
        FRONT_TO_BACK
    };

    struct BatchInfo
    {
        float x, y;
        float r, g, b, a;
        float sX, sY, sW, sH;
        float originX, originY;
        float scaleX, scaleY;
        float rotation;
        float depth;
        float alpha;
    };

}

#endif
