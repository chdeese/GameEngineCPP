#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

Physics::Collision* Physics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 direction = otherPosition - position;
	float distance = direction.getMagnitude();

	if (distance > other->getRadius() + m_width && distance > other->getRadius() + m_height)
		return nullptr;

	Physics::Collision* collisionData = new Collision();
	collisionData->collider = other;

	float widthSign = 1;
	float heightSign = 1;

	if(direction.x < 0)
		widthSign = -widthSign;
	if (direction.y < 0)
		heightSign = -heightSign;

	GameMath::Vector2 otherContactCorner = other->getOwner()->getTransform()->getGlobalPosition();
	otherContactCorner = otherContactCorner + GameMath::Vector2({m_width * widthSign, m_height * heightSign});

	GameMath::Vector2 contactCorner = getOwner()->getTransform()->getGlobalPosition();

	collisionData->contactPoint = position + (direction.getNormalized() /* *radius */);
	collisionData->penetrationDistance = (other->getRadius() /* + radius */) - distance;

	return collisionData;
}

Physics::Collision* Physics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	return nullptr;
}

void Physics::AABBColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	RAYLIB_H::DrawRectangleLines(position.x, position.y, m_radius, m_radius, GetColor(getColor()));
}