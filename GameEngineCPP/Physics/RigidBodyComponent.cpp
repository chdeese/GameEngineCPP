#include "RigidBodyComponent.h"
#include "Engine/TransformComponent.h"
#include "Engine/Entity.h"
#include "Physics/ColliderComponent.h"

void Physics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	m_velocity = m_velocity + (force / getMass());
}

void Physics::RigidBodyComponent::applyForceToEntity(RigidBodyComponent* rigidBody, GameMath::Vector2 force)
{
	rigidBody->applyForce(force * -1);
	applyForce(force);
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
		if (rigidBodyOther->getMass() == getMass() && 1 == dot(collisionData->normal, collisionData->normal))
			j = getMass() * dot(getVelocity() - rigidBodyOther->getVelocity(), collisionData->normal);
		else
			j = (2 * dot(getVelocity() - rigidBodyOther->getVelocity(), collisionData->normal) / (dot(collisionData->normal, collisionData->normal) * ((1 / getMass()) + (1 / rigidBodyOther->getMass()))));

		force = (collisionData->normal * -j);
		applyForceToEntity(rigidBodyOther, force);
	}
	else
	{
		j = 2 * getMass() * dot(getVelocity(), collisionData->normal);
		force = (collisionData->normal * -j);
		applyForce(force);
	}


}

void Physics::RigidBodyComponent::onCollisionEnter(Physics::Collision* other)
{
	if (!other->collider->getRigidBody())
		return;

	//other->collider->getRigidBody()->setVelocity(m_velocity);
}
