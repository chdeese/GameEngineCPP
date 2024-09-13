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
	direction  = direction.getNormalized();

	GameMath::Vector2 contactPoint = position + (direction.getNormalized() * other->getRadius());
	float topY = position.y - getHeight() / 2;
	float bottomY = position.y + getHeight() / 2;
	float leftX = position.x - getWidth() / 2;
	float rightX = position.x + getWidth() / 2;


	if (contactPoint.y < topY && contactPoint.y > bottomY
		&& contactPoint.x < leftX && contactPoint.x > rightX)
	{
		return nullptr;
	}

	DrawCircle(contactPoint.x, contactPoint.y, 1, GREEN);

	Physics::Collision* collisionData = new Collision();

	collisionData->collider = other;
	collisionData->contactPoint = contactPoint;

	float colliderAABBMagnitude = (collisionData->contactPoint - position).getMagnitude();
	float penetrationDistance = distance = (other->getRadius() + colliderAABBMagnitude);

	if (penetrationDistance < 0)
		penetrationDistance = -penetrationDistance;

	collisionData->penetrationDistance = penetrationDistance;

	float x = 0; 
	float y = 0;
	//direction is normalized
	if (direction.x < direction.y)
	{
		y++;
		if (direction.y < 0)
			y = -y;
			
	}
	else
	{
		x++;
		if (direction.x < 0)
			x = -x;
		
	}
	collisionData->normal = GameMath::Vector2({ x, y }).getNormalized();

	return collisionData;
}

Physics::Collision* Physics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 direction = otherPosition - position;
	float distance = direction.getMagnitude();

	float combinedWidth = other->getWidth() + getWidth();
	float combinedHeight = other->getHeight() + getHeight();

	float widthSign = 1;
	float heightSign = 1;

	if (direction.x < 0)
		widthSign = -widthSign;
	if (direction.y < 0)
		heightSign = -heightSign;

	GameMath::Vector2 otherContactCorner = other->getOwner()->getTransform()->getGlobalPosition();
	otherContactCorner = otherContactCorner + GameMath::Vector2({ (other->getWidth() / 2) * widthSign, (other->getHeight() / 2) * heightSign });

	GameMath::Vector2 contactCorner = position + GameMath::Vector2({ (m_width / 2) * widthSign, (m_height / 2) * heightSign });

	float combinedCorners = (contactCorner - position).getMagnitude() + (otherContactCorner - otherPosition).getMagnitude();

	GameMath::Vector2 cornerToOther = otherContactCorner - contactCorner;

	if (cornerToOther.x < 0)
		cornerToOther.x = -cornerToOther.x;
	if (cornerToOther.y < 0)
		cornerToOther.y = -cornerToOther.y;


	Physics::Collision* collisionData = new Collision();
	collisionData->collider = other;



	//halfway between both contact corner points
	collisionData->contactPoint = (otherContactCorner - contactCorner) / 2;

	float penetrationDistance = ((collisionData->contactPoint - otherPosition).getMagnitude() + (collisionData->contactPoint - position).getMagnitude()) - distance;
	if (penetrationDistance < 0)
		penetrationDistance = -penetrationDistance;

	collisionData->penetrationDistance = penetrationDistance;
	collisionData->contactPoint = position + (direction.getNormalized() /* *radius */);
	collisionData->penetrationDistance = distance - (other->getWidth() + (collisionData->contactPoint - position).getMagnitude());

	return collisionData;
}

void Physics::AABBColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	float offset = 2.0f;

	RAYLIB_H::DrawRectangleLines(position.x - (m_width / 2) - offset, position.y - (m_height / 2) - offset, m_width + (offset * 2), m_height + (offset * 2), GetColor(getColor()));
}