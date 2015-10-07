#include <vix_aabb.h>

namespace Vixen {

    AABB::AABB(Vector3 centroid, Vector3 halfSize)
    {

    }

    AABB::~AABB()
    {

    }

    Vector3 AABB::Max() const
    {
        return m_max;
    }

    Vector3 AABB::Min() const
    {
        return m_min;
    }

    Vector3 AABB::Centroid() const
    {
        return m_centroid;
    }

    Vector3 AABB::Size() const
    {
        return m_size;
    }

    void AABB::UpdateTransformed()
    {
        //We need to recalculate the centroid and size and min and max,
        //based on the transformed model. To do this, we need the vertices of the model again

    }

    void AABB::VUpdate(float dt)
    {

    }

    bool AABB::CheckCollision(AABB* a, AABB* b)
    {
        bool colliding = true;

        Vector3 aMin = a->Min();
        Vector3 aMax = a->Max();
        Vector3 bMin = b->Min();
        Vector3 bMax = b->Max();

        if (aMax.x < bMin.x || aMin.x > bMax.y)
            colliding = false;
        else if (aMax.y < bMin.y || aMin.y > bMax.y)
            colliding = false;
        else if (aMax.z < bMin.z || aMin.z > bMax.z)
            colliding = false;

        return colliding;
    }
}