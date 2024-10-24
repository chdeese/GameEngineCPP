#include "ColliderComponent.h"
#include "Engine/Engine.h"
#include "Engine/Scene.h"
#include "Engine/Entity.h"
#include "Physics/RigidBodyComponent.h"

void Physics::ColliderComponent::start()
{
	Engine::Engine::getCurrentScene()->addActiveCollider(this);
	m_rigidBody = getOwner()->getComponent<Physics::RigidBodyComponent>();
}

Physics::Collision* Physics::ColliderComponent::checkCollision(ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case CIRCLE:
		return checkCollisionCircle((CircleColliderComponent*)other);
	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);
	}

	return nullptr;
}

void Physics::ColliderComponent::onCollisionEnter(Physics::Collision* other)
{
	switch (getColliderType())
	{
	case CIRCLE:
		m_color = 0xFF0000FF;
		break;
	
	case AABB:
		m_color = 0xFF0000FF;
		break;
	}
	
}

void Physics::ColliderComponent::update(double deltaTime)
{
	m_color = 0x00FF00FF;
}
