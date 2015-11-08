#include <vix_bulletsimulator.h>

namespace Vixen {

	void BulletSimulator::Initialize(btVector3 gravity)
	{
		BulletSimulator& _simulator = BulletSimulator::instance();

		_simulator.m_broadPhase = new btDbvtBroadphase;
		_simulator.m_collisionConfig = new btDefaultCollisionConfiguration;
		_simulator.m_collisionDispatcher = new btCollisionDispatcher(_simulator.m_collisionConfig);
		_simulator.m_constraintSolver = new btSequentialImpulseConstraintSolver;
		_simulator.m_world = new btDiscreteDynamicsWorld(_simulator.m_collisionDispatcher,
			_simulator.m_broadPhase, _simulator.m_constraintSolver, _simulator.m_collisionConfig);
		_simulator.m_world->setGravity(gravity);
	}

	void BulletSimulator::DeInitialize()
	{
		BulletSimulator& _simulator = BulletSimulator::instance();

		delete _simulator.m_world;
		delete _simulator.m_constraintSolver;
		delete _simulator.m_collisionDispatcher;
		delete _simulator.m_collisionConfig;
		delete _simulator.m_broadPhase;
	}

	void BulletSimulator::Step(float time)
	{
		BulletSimulator& _simulator = BulletSimulator::instance();

		_simulator.m_world->stepSimulation(time);
	}
}