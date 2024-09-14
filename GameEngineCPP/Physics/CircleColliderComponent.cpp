#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/AABBColliderComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

Physics::Collision* Physics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 direction = otherPosition - position;
	float distance = direction.getMagnitude();

	if(distance > other->m_radius + m_radius)
		return nullptr;

	Physics::Collision* collisionData = new Collision();
	collisionData->collider = other;
	collisionData->normal = direction.getNormalized();
	collisionData->contactPoint = position + (direction.getNormalized() * getRadius());
	collisionData->penetrationDistance = (other->m_radius + m_radius) - distance;

	return collisionData;
}

Physics::Collision* Physics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	Physics::Collision* collisionData = other->checkCollisionCircle(this);

	if (!collisionData)
		return nullptr;

	collisionData->collider = other;
	GameMath::Vector2 normal = collisionData->normal;
	collisionData->normal = GameMath::Vector2({ -normal.x, -normal.y });

	return collisionData;
}

void Physics::CircleColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(getColor()));
}
