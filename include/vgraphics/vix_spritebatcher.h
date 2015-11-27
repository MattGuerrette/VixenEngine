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
