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
	collisionData->contactPoint = position + (collisionData->normal * getRadius());
	collisionData->penetrationDistance = (other->m_radius + m_radius) - distance;

	return collisionData;
}

Physics::Collision* Physics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 toOther = otherPosition - position;


	float distanceX = abs(toOther.x);
	float distanceY = abs(toOther.y);
	toOther = toOther.getNormalized();

	float widthSum = (other->getWidth() / 2) + getRadius();
	float heightSum = (other->getHeight() / 2) + getRadius();

	if (distanceX > widthSum || distanceY > heightSum)
		return nullptr;

	Physics::Collision* collisionData = new Collision();

	float penetrationDistance;
	GameMath::Vector2 normal;
	GameMath::Vector2 contactPoint;

	float yPos = 1;
	float xPos = 1;

	if (toOther.x < 0)
		xPos = -xPos;
	if (toOther.y < 0)
		yPos = -yPos;

	GameMath::Vector2 nearestCorner = position + GameMath::Vector2(xPos * (other->getWidth() / 2), yPos * (other->getHeight() / 2));

	float xPen = (other->getWidth() / 2) + getRadius() - distanceX;
	float yPen = (other->getHeight() / 2) + getRadius() - distanceY;

	if (xPen < yPen)
	{
		normal = GameMath::Vector2({ xPos, 0 });

		penetrationDistance = xPen;

		contactPoint = GameMath::Vector2({ nearestCorner.x, otherPosition.y });
	}
	else
	{
		normal = GameMath::Vector2({ 0, yPos });

		penetrationDistance = yPen;

		contactPoint = GameMath::Vector2({ otherPosition.x, nearestCorner.y });
	}

	collisionData->collider = other;
	collisionData->normal = normal;
	collisionData->contactPoint = contactPoint;
	collisionData->penetrationDistance = penetrationDistance;

	return collisionData;
}

void Physics::CircleColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(getColor()));
}
