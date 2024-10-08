#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/RigidBodyComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

Physics::Collision* Physics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 toOther = otherPosition - position;


	float distanceX = abs(toOther.x);
	float distanceY = abs(toOther.y);
	toOther  = toOther.getNormalized();

	float widthSum = (getWidth() / 2) + other->getRadius();
	float heightSum = (getHeight() / 2) + other->getRadius();

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

	GameMath::Vector2 nearestCorner = position + GameMath::Vector2(xPos * (getWidth() / 2), yPos * (getHeight() / 2));

	float xPen = (getWidth() / 2) + other->getRadius() - distanceX;
	float yPen = (getHeight() / 2) + other->getRadius() - distanceY;

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

Physics::Collision* Physics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 toOther = otherPosition - position;

	float distanceX = abs(toOther.x); 
	float distanceY = abs(toOther.y);
	toOther.normalize();

	float widthSum = getWidth() + other->getWidth();
	float heightSum = getHeight() + other->getHeight();

	if (distanceX > widthSum / 2 || distanceY > heightSum / 2)
		return nullptr;

	Collision* collisionData = new Collision();

	float xPen = (widthSum / 2) - distanceX;
	float yPen = (heightSum / 2) - distanceY;

	float penetrationDistance;
	GameMath::Vector2 normal;
	GameMath::Vector2 contactPoint;

	float xPos = toOther.x * (getWidth() / 2);
	float yPos = toOther.y * (getHeight() / 2);

	if (toOther.x < 0)
		xPos = -xPos;
	if (toOther.y < 0)
		yPos = -yPos;

	contactPoint = position + GameMath::Vector2(xPos, yPos);

	if (xPen < yPen)
	{
		penetrationDistance = xPen;
		if (toOther.x > 0)
			normal = GameMath::Vector2(1, 0);
		else
			normal = GameMath::Vector2(-1, 0);
	}
	else
	{
		penetrationDistance = yPen;
		if (toOther.y > 0)
			normal = GameMath::Vector2(0, 1);
		else
			normal = GameMath::Vector2(0, -1);
	}


	collisionData->collider = other;
	collisionData->normal = normal;
	collisionData->contactPoint = contactPoint;
	collisionData->penetrationDistance = penetrationDistance;

	return collisionData;
}

void Physics::AABBColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	float offset = 2.0f;

	RAYLIB_H::DrawRectangleLines(position.x - (m_width / 2) - offset, position.y - (m_height / 2) - offset, m_width + (offset * 2), m_height + (offset * 2), GetColor(getColor()));
}