#ifndef VIX_AABB_H
#define VIX_AABB_H

#include <vix_platform.h>
#include <vix_transform.h>
#include <vix_component.h>

namespace Vixen {

    class VIX_API AABB : public IComponent
    {
    public:
        AABB(Vector3 centroid, Vector3 halfSize);

        ~AABB();


        Vector3 Min() const;
        Vector3 Max() const;
        Vector3 Centroid() const;
        Vector3 Size() const;


        void VUpdate(float dt) override;

        static bool CheckCollision(AABB* a, AABB* b);

    private:
        void UpdateTransformed();

    private:
        Vector3 m_position;
        Vector3 m_centroid;
        Vector3 m_size;
        Vector3 m_min;
        Vector3 m_max;
        
        Transform* m_parent;
    };

}

#endif