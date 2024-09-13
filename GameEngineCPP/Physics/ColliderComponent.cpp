#include "ColliderComponent.h"
#include "Engine/Engine.h"
#include "Engine/Scene.h"

void Physics::ColliderComponent::start()
{
	Engine::Engine::getCurrentScene()->addActiveCollider(this);
	// Get owner's rigidbody
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
		m_color = 0x2222FFFF;
		break;
	}
	
}

void Physics::ColliderComponent::update(double deltaTime)
{
	m_color = 0x00FF00FF;
}
