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


	float topY = position.y - (getHeight() / 2);
	float bottomY = position.y + (getHeight() / 2);
	float leftX = position.x - (getWidth() / 2);
	float rightX = position.x + (getWidth() / 2);
	float dirID = 0;


	float topCircleY = otherPosition.y - (other->getRadius());
	float bottomCircleY = otherPosition.y + (other->getRadius());
	float leftCircleX = otherPosition.x - (other->getRadius());
	float rightCircleX = otherPosition.x + (other->getRadius());



	if  (  (topY > bottomCircleY) 
		|| (bottomY < topCircleY) 
		|| (leftX > rightCircleX)
		|| (rightX < leftCircleX)
		)
	{
		return nullptr;
	}

	Physics::Collision* collisionData = new Collision();


	float topPen = (bottomCircleY - topY);
	float bottomPen = (bottomY - topCircleY);
	float leftPen = (rightCircleX - leftX);
	float rightPen = (rightX - leftCircleX);

	//needs to be larger than any possible width
	float lowest = 9999999;
	GameMath::Vector2 normal;
	if (topPen > 0)
	{
		lowest = topPen;
		normal = GameMath::Vector2({0, -1});
	}
	if (bottomPen > 0 && bottomPen < lowest)
	{
		lowest = bottomPen;
		normal = GameMath::Vector2({0, 1});
	}
	if (leftPen > 0 && leftPen < lowest)
	{
		lowest = leftPen;
		normal = GameMath::Vector2({-1, 0});
	}
	if (rightPen > 0 && rightPen < lowest)
	{
		lowest = rightPen;
		normal = GameMath::Vector2({1, 0});
	}

	GameMath::Vector2 circleContactPoint = GameMath::Vector2({ -normal.x, -normal.y }) * other->getRadius();
	GameMath::Vector2 contactPoint;
	if (abs(normal.x) > abs(normal.y))
	{
		contactPoint = position + (normal * (getWidth() / 2));
		contactPoint.y = circleContactPoint.y;
	}
	else
	{
		contactPoint = position + (normal * (getHeight() / 2));
		contactPoint.x = circleContactPoint.x;
	}



	collisionData->normal = normal;
	collisionData->penetrationDistance = lowest;
	collisionData->contactPoint = contactPoint;
	collisionData->collider = other;

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

	float leftOverlapDistance = -(leftX - rightXOther);
	float rightOverlapDistance = rightX - leftXOther;
	float upOverlapDistance = -(topY - bottomYOther);
	float downOverlapDistance = bottomY - topYOther;
	

	float bothWidth = getWidth() + other->getWidth();
	float bothHeight = getHeight() + other->getHeight();

	// x > 0 if overlapping
	if (leftOverlapDistance > bothWidth)
		leftOverlapDistance = 0;
	if (rightOverlapDistance > bothWidth)
		rightOverlapDistance = 0;
	if (upOverlapDistance > bothHeight)
		upOverlapDistance = 0;
	if (downOverlapDistance > bothHeight)
		downOverlapDistance = 0;


	Physics::Collision* collisionData = new Collision();

	GameMath::Vector2 directionNormalized = direction.getNormalized();

	GameMath::Vector2 normal;
	float penetrationDistance;
	bool xPos = directionNormalized.x > 0;
	bool yPos = directionNormalized.y > 0;
	if (rightOverlapDistance > leftOverlapDistance)
	{
		if (upOverlapDistance > downOverlapDistance)
		{
			if (upOverlapDistance > rightOverlapDistance)
			{
				penetrationDistance = rightOverlapDistance;

				normal = GameMath::Vector2(1, 0);
			}
			else
			{
				penetrationDistance = upOverlapDistance;

				normal = GameMath::Vector2(0, -1);
			}
		}
		else
		{
			if (downOverlapDistance > rightOverlapDistance)
			{
				penetrationDistance = rightOverlapDistance;
				normal = GameMath::Vector2(1, 0);
			}
			else
			{
				penetrationDistance = downOverlapDistance;
				normal = GameMath::Vector2(0, 1);
			}
		}
	}
	else
	{
		if (upOverlapDistance > downOverlapDistance)
		{
			if (upOverlapDistance > leftOverlapDistance)
			{
				penetrationDistance = leftOverlapDistance;
				normal = GameMath::Vector2(-1, 0);
			}
			else
			{
				penetrationDistance = upOverlapDistance;
				normal = GameMath::Vector2(0, -1);
			}
		}
		else
		{
			if (downOverlapDistance > leftOverlapDistance)
			{
				penetrationDistance = leftOverlapDistance;
				normal = GameMath::Vector2(-1, 0);
			}
			else
			{
				penetrationDistance = downOverlapDistance;
				normal = GameMath::Vector2(0, 1);
			}
		}
	}



	GameMath::Vector2 contactSide;
	GameMath::Vector2 contactSideOther;
	if (abs(direction.x) > abs(direction.y))
	{
		contactSide = position + (normal * (getWidth() / 2));
		contactSideOther = otherPosition + ((GameMath::Vector2(-normal.x, -normal.y) * (other->getWidth() / 2)));
	}
	else
	{
		contactSide = position + (normal * (getHeight() / 2));
		contactSideOther = otherPosition + ((GameMath::Vector2(-normal.x, -normal.y) * (other->getHeight() / 2)));
	}

	GameMath::Vector2 contactPoint = (contactSide - contactSideOther) / 2;

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