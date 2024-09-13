#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>

Physics::Collision* Physics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	/*float minRadius = GameMath::Vector2({position.x - (m_width / 2), position.y}).getMagnitude();
	float maxRadius = (contactCorner - position).getMagnitude();*/

	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 direction = otherPosition - position;

	float originDistance = direction.getMagnitude();
	direction  = direction.getNormalized();

	float widthSign = 1;
	float heightSign = 1;


	if (direction.x < 0)
		widthSign = -widthSign;
	if (direction.y < 0)
		heightSign = -heightSign;


	GameMath::Vector2 contactCorner = position + GameMath::Vector2({ (m_width / 2) * widthSign, (m_height / 2) * heightSign });

	GameMath::Vector2 circleEdgeToCorner = (contactCorner - otherPosition).getNormalized() * other->getRadius();


	GameMath::Vector2 circleCenterPoint;


	float distanceToCenterPoint;
	float absoluteX = direction.x;
	if (absoluteX < 0)
		absoluteX = -absoluteX;
	float absoluteY = direction.y;
	if (absoluteY < 0)
		absoluteY = -absoluteY;

	GameMath::Vector2 sideCenterPoint;

	if (absoluteX > absoluteY)
	{
		distanceToCenterPoint = absoluteX * widthSign;
		sideCenterPoint = GameMath::Vector2({ position.x + distanceToCenterPoint, position.y });
	}
	else
	{
		distanceToCenterPoint = absoluteY * heightSign;
		sideCenterPoint = GameMath::Vector2({position.x, position.y + distanceToCenterPoint });
	}
	
	float circleEdgeToSideDistance = (sideCenterPoint - otherPosition).getMagnitude() - other->getRadius();

	float circleEdgeToCornerDistance = (contactCorner - circleEdgeToCorner).getMagnitude();

	if (circleEdgeToCornerDistance - other->getRadius() > 0.001f && circleEdgeToSideDistance - other->getRadius() > 0.001f)
		return nullptr;

	Physics::Collision* collisionData = new Collision();
	collisionData->collider = other;

	GameMath::Vector2 directionInverse = GameMath::Vector2({direction.y, -direction.x});


	//position between circle radius and nearest the corner.
	collisionData->contactPoint = contactCorner - (directionInverse.getNormalized() * other->getRadius())
								/ 2;
	collisionData->normal = (collisionData->contactPoint - otherPosition).getNormalized();

	//float minMax = dot((contactCorner - position), (collisionData->contactPoint));

	float colliderAABBMagnitude = (collisionData->contactPoint - position).getMagnitude();
	float penetrationDistance = (other->getRadius() + colliderAABBMagnitude) - originDistance;
	if (penetrationDistance < 0)
		penetrationDistance = -penetrationDistance;

	collisionData->penetrationDistance = penetrationDistance;

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


	//GameMath::Vector2 contactCornerToOtherPosition = otherPosition - contactCorner;

	//if(dot(
	//	otherContactCorner - contactCorner, /*perpendicular*/GameMath::Vector2({contactCornerToOtherPosition.y, -contactCornerToOtherPosition.x})
	//	  ) 
	//	> 0
	//   )

	//if (
	//	
	//		((otherContactCorner - otherPosition).getMagnitude() >) ||
	//	
	//   )
	//	return nullptr;

	Physics::Collision* collisionData = new Collision();
	collisionData->collider = other;



	//halfway between both contact corner points
	collisionData->contactPoint = (otherContactCorner - contactCorner) / 2;

	float penetrationDistance = ((collisionData->contactPoint - otherPosition).getMagnitude() + (collisionData->contactPoint - position).getMagnitude()) - distance;

	if (penetrationDistance < 0)
		penetrationDistance = -penetrationDistance;

	collisionData->penetrationDistance = penetrationDistance;

	return collisionData;
}

void Physics::AABBColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	float offset = 2.0f;

	RAYLIB_H::DrawRectangleLines(position.x - (m_width / 2) - offset, position.y - (m_height / 2) - offset, m_width + (offset * 2), m_height + (offset * 2), GetColor(getColor()));
}