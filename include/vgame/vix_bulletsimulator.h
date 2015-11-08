#ifndef VIX_BULLETSIMULATOR_H
#define VIX_BULLETSIMULATOR_H

#include <vix_platform.h>
#include <vix_singleton.h>

#include <vix_bullet.h>

namespace Vixen {

	class VIX_API BulletSimulator : public Singleton<BulletSimulator>
	{
	public:
		static void Initialize(btVector3 gravity);

		static void DeInitialize();

		static void Step(float time);

	private:
		btDynamicsWorld*						m_world;
		btBroadphaseInterface*					m_broadPhase;
		btCollisionConfiguration*				m_collisionConfig;
		btCollisionDispatcher*					m_collisionDispatcher;
		btSequentialImpulseConstraintSolver*	m_constraintSolver;
	};

}

#endif