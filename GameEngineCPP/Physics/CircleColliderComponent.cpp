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
	GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector2 direction = otherPosition - position;

	float originDistance = direction.getMagnitude();
	direction = direction.getNormalized();

	float widthSign = 1;
	float heightSign = 1;


	if (direction.x < 0)
		widthSign = -widthSign;
	if (direction.y < 0)
		heightSign = -heightSign;


	GameMath::Vector2 otherContactCorner = position + GameMath::Vector2({ (other->getWidth() / 2) * widthSign, (other->getHeight() / 2) * heightSign });

	GameMath::Vector2 circleEdgeToCorner = (otherContactCorner - otherPosition).getNormalized() * m_radius;


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
		sideCenterPoint = GameMath::Vector2({ position.x, position.y + distanceToCenterPoint });
	}

	float circleEdgeToSideDistance = (sideCenterPoint - otherPosition).getMagnitude() - m_radius;

	float circleEdgeToCornerDistance = (otherContactCorner - circleEdgeToCorner).getMagnitude();

	if (circleEdgeToCornerDistance - m_radius > 0.001f && circleEdgeToSideDistance - m_radius > 0.001f)
		return nullptr;

	Physics::Collision* collisionData = new Collision();
	collisionData->collider = other;

	GameMath::Vector2 directionInverse = GameMath::Vector2({ direction.y, -direction.x });


	//position between circle radius and nearest the corner.
	collisionData->contactPoint = otherContactCorner - (direction.getNormalized() * m_radius)
		/ 2;

	GameMath::Vector2 toOther = collisionData->contactPoint - position;

	collisionData->normal = GameMath::Vector2(toOther.y, -toOther.x).getNormalized();

	//float minMax = dot((contactCorner - position), (collisionData->contactPoint));

	float colliderAABBMagnitude = (collisionData->contactPoint - otherPosition).getMagnitude();
	float penetrationDistance = (m_radius + colliderAABBMagnitude) - originDistance;
	if (penetrationDistance < 0)
		penetrationDistance = -penetrationDistance;

	collisionData->penetrationDistance = penetrationDistance;

	return collisionData;
}

void Physics::CircleColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius() - 5, GetColor(getColor()));
}
