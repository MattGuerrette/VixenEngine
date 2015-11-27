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

#include <vix_rigidbody_component.h>
#include <vix_gameobject.h>
#include <vix_bulletsimulator.h>

namespace Vixen {

	RigidBodyComponent::RigidBodyComponent()
		: Component(Component::Type::PHYSICS_RIGIDBODY)
	{
		m_friction = 0.0f;
		m_mass = 1.0f;
		m_restitution = 0.0f;
		m_colliderShape = NULL;
	}

	RigidBodyComponent::~RigidBodyComponent()
	{

	}

	void RigidBodyComponent::VOnInit()
	{
		Vector3 position = m_parent->GetTransform()->GetWorldPosition();
		Vector3 rotation = m_parent->GetTransform()->GetRotation();
		btTransform transform;
		transform.setOrigin(btVector3(position.x, position.y, position.z));
		transform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, 1.0f));
		m_motionState = new btDefaultMotionState(transform, btTransform(btQuaternion(0, -1, 0, 1)));

		//construct the collider shape
		m_colliderShape->VConstruct();

		btVector3 inertia;
		m_colliderShape->GetShape()->calculateLocalInertia(m_mass, inertia);

		btRigidBody::btRigidBodyConstructionInfo info(m_mass, m_motionState, m_colliderShape->GetShape(), inertia);
		info.m_friction = m_friction;
		info.m_restitution = m_restitution;

		m_rigidBody = new btRigidBody(info);

		BulletSimulator::AddRigidBody(m_rigidBody);
	}

	void RigidBodyComponent::VOnEnable()
	{

	}

	void RigidBodyComponent::VUpdate()
	{
		Transform* _transform = m_parent->GetTransform();

		btTransform _physicsTransform;
		m_motionState->getWorldTransform(_physicsTransform);

		_transform->SetPosition(Vector3(_physicsTransform.getOrigin().x(),
										_physicsTransform.getOrigin().y(),
										_physicsTransform.getOrigin().z()));
	}

	void RigidBodyComponent::VOnDisable()
	{

	}

	void RigidBodyComponent::VOnDestroy()
	{

	}

	void RigidBodyComponent::SetFriction(btScalar friction)
	{
		m_friction = friction;
	}

	void RigidBodyComponent::SetMass(btScalar mass)
	{
		m_mass = mass;
	}

	void RigidBodyComponent::SetRestitution(btScalar restitution)
	{
		m_restitution = restitution;
	}

	void RigidBodyComponent::SetColliderShape(BulletColliderShape* shape)
	{
		m_colliderShape = shape;
	}

}
