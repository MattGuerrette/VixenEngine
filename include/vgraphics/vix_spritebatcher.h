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
