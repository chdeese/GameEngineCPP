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
	GameMath::Vector2 direction = otherPosition - position;
	GameMath::Vector2 toCircle = direction;
	float distance = direction.getMagnitude();
	direction  = direction.getNormalized();

	Physics::Collision* collisionData = new Collision();

	GameMath::Vector2 normal;
	GameMath::Vector2 contactPoint;
	float penetrationDistance;

	float heightSign = 1;
	float widthSign = 1;

	if (direction.x < 0)
		widthSign = -widthSign;
	if (direction.y < 0)
		heightSign = -heightSign;

	GameMath::Vector2 nearestCorner = position + GameMath::Vector2({ widthSign * (getWidth() / 2), heightSign * (getHeight() / 2) });

	float circleToCornerDistance = (nearestCorner - otherPosition).getMagnitude();
	float xDistance = abs(otherPosition.x - position.x);
	float yDistance = abs(otherPosition.y - position.y);
	
	bool xAligned = false;
	bool yAligned = false;

	if (xDistance < (getWidth() / 2) + other->getRadius())
		xAligned = true;
	if (yDistance < (getHeight() / 2) + other->getRadius())
		yAligned = true;
	if (!xAligned || !yAligned)
		return nullptr;
	if ((getWidth() / 2) + other->getRadius() - xDistance < (getHeight() / 2) + other->getRadius() - yDistance)
	{
		normal = GameMath::Vector2({ widthSign, 0 });

		penetrationDistance = ((getWidth() / 2) + other->getRadius()) - abs(otherPosition.x - position.x);

		contactPoint = GameMath::Vector2({ nearestCorner.x, otherPosition.y });
	}
	else
	{
		normal = GameMath::Vector2({ 0, heightSign });

		penetrationDistance = ((getHeight() / 2) + other->getRadius()) - abs(otherPosition.y - position.y);

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
	float distance = toOther.getMagnitude();

	float distanceX = toOther.x; 
	float distanceY = toOther.y;

	float widthSum = getWidth() + other->getWidth();
	float heightSum = getHeight() + other->getHeight();

	if (abs(distanceX) > widthSum / 2 || abs(distanceY) > heightSum / 2)
		return nullptr;

	Collision* collisionData = new Collision();

	float overlapX = (widthSum / 2) - distanceX;
	float overlapY = (heightSum / 2) - distanceY;

	float penetrationDistance;
	GameMath::Vector2 normal;
	GameMath::Vector2 contactPoint;
	GameMath::Vector2 nearestCorner;


	if (overlapX > overlapY)
	{
		penetrationDistance = overlapY;
		if (toOther.y > 0)
			normal = GameMath::Vector2(0, 1);
		else
			normal = GameMath::Vector2(0, -1);
	}
	else
	{
		penetrationDistance = overlapX;
		if (toOther.x > 0)
			normal = GameMath::Vector2(1, 0);
		else
			normal = GameMath::Vector2(-1, 0);
	}

	toOther.normalize();

	float xPos = toOther.x * (getWidth() / 2);
	float yPos = toOther.y * (getHeight() / 2);
	if (toOther.x < 0)
		xPos = -xPos;
	if (toOther.y < 0)
		yPos = -yPos;

	contactPoint = position + GameMath::Vector2(xPos, yPos);

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