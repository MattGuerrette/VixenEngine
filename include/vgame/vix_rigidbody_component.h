#ifndef VIX_RIGIDBODY_COMPONENT_H
#define VIX_RIGIDBODY_COMPONENT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_bullet.h>
#include <vix_bullet_collidershape.h>

namespace Vixen {

	class VIX_API RigidBodyComponent : public Component
	{
	public:
		RigidBodyComponent();

		~RigidBodyComponent();

		void VOnInit();
		void VOnEnable();
		void VUpdate();
		void VOnDisable();
		void VOnDestroy();


		void SetFriction(btScalar friction);
		void SetMass(btScalar mass);
		void SetRestitution(btScalar restitution);

		void SetColliderShape(BulletColliderShape* shape);

	private:
		btRigidBody*			m_rigidBody;
		btMotionState*			m_motionState;
		btVector3				m_motionStateQuat;
		btVector3				m_motionStateOrigin;
		btScalar				m_friction;
		btScalar				m_restitution;
		btScalar				m_mass;
		btVector3				m_inertia;
		BulletColliderShape*	m_colliderShape;
	};

}

#endif
