#include "RigidBodyComponent.h"
#include "Engine/TransformComponent.h"
#include "Engine/Entity.h"
#include "Physics/ColliderComponent.h"

void Physics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	m_velocity = m_velocity + force / getMass();
}

void Physics::RigidBodyComponent::applyForceToEntity(RigidBodyComponent* rigidBody, GameMath::Vector2 force)
{
	applyForce(force * -1);
	rigidBody->applyForce(force);
}

void Physics::RigidBodyComponent::fixedUpdate(float fixedDeltaTime)
{
	GameMath::Vector2 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + m_velocity * fixedDeltaTime);

	GameMath::Vector2 gravity = { 0, getGravity() };
	applyForce(gravity * getMass());
}

void Physics::RigidBodyComponent::resolveCollision(Physics::Collision* collisionData)
{

	RigidBodyComponent* rigidBodyOther = collisionData->collider->getRigidBody();

	float j;
	GameMath::Vector2 force;


	if (rigidBodyOther)
	{
		if (rigidBodyOther->getMass() == getMass())
			j = getMass() * dot(getVelocity() - rigidBodyOther->getVelocity(), collisionData->normal);
		else
			j = (2 * dot(getVelocity() - rigidBodyOther->getVelocity(), collisionData->normal) / (dot(collisionData->normal, collisionData->normal) * ((1 / getMass()) + (1 / rigidBodyOther->getMass()))));

		force = collisionData->normal * -j;
		applyForce(force);
	}
	else
	{
		j = 2 * getMass() * dot(collisionData->normal, getVelocity());
		force = GameMath::Vector2(collisionData->normal.x, collisionData->normal.y) * -j;
		applyForce(force);
	}


}

void Physics::RigidBodyComponent::onCollisionEnter(Physics::Collision* other)
{
	resolveCollision(other);
}
