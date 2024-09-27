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
	GameMath::Vector2 direction = otherPosition - position;
	float distance = direction.getMagnitude();

	float topY = position.y - (getHeight() / 2);
	float bottomY = position.y + (getHeight() / 2);
	float leftX = position.x - (getWidth() / 2);
	float rightX = position.x + (getWidth() / 2);

	float topYOther = otherPosition.y - (other->getHeight() / 2);
	float bottomYOther = otherPosition.y + (other->getHeight() / 2);
	float leftXOther = otherPosition.x - (other->getWidth() / 2);
	float rightXOther = otherPosition.x + (other->getWidth() / 2);

	float sensitivity = 0.01f;



	if ((leftX > rightXOther) || (rightX < leftXOther) || (topY > bottomYOther) || (bottomY < topYOther))
		return nullptr;


	Physics::Collision* collisionData = new Collision();
	GameMath::Vector2 normal;
	float penetrationDistance;

	float heightSign = 1;
	float widthSign = 1;

	if (direction.x < 0)
		widthSign = -widthSign;
	if (direction.y < 0)
		heightSign = -heightSign;

	GameMath::Vector2 nearestCorner = position + GameMath::Vector2({ widthSign * (getWidth() / 2), heightSign * (getHeight() / 2) });
	GameMath::Vector2 nearestCornerOther = otherPosition + GameMath::Vector2({ -widthSign * (other->getWidth() / 2), -heightSign * (getHeight() / 2) });
	GameMath::Vector2 contactPoint = (nearestCorner - nearestCornerOther) / 2;


	float cornerXDistance = abs(nearestCorner.x - nearestCornerOther.x);
	float cornerYDistance = abs(nearestCorner.y - nearestCornerOther.y);

	if(cornerXDistance > cornerYDistance)
	{
		normal = GameMath::Vector2({ 0, direction.y}).getNormalized();
		penetrationDistance = cornerYDistance;
	}
	else
	{
		normal = GameMath::Vector2({ direction.x, 0 }).getNormalized();
		penetrationDistance = cornerXDistance;
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