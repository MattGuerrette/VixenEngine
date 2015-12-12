
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

		static void AddRigidBody(btRigidBody* body);

		static void RemoveRigidBody(btRigidBody* body);

	private:
		btDynamicsWorld*						m_world;
		btBroadphaseInterface*					m_broadPhase;
		btCollisionConfiguration*				m_collisionConfig;
		btCollisionDispatcher*					m_collisionDispatcher;
		btSequentialImpulseConstraintSolver*	m_constraintSolver;
	};

}

#endif

