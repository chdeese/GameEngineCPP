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



	GameMath::Vector2 contactPoint = otherPosition + ((GameMath::Vector2({-direction.x, -direction.y}).getNormalized()) * other->getRadius());
	float topY = position.y - (getHeight() / 2);
	float bottomY = position.y + (getHeight() / 2);
	float leftX = position.x - (getWidth() / 2);
	float rightX = position.x + (getWidth() / 2);


	if ((topY > contactPoint.y) || (bottomY < contactPoint.y) || (leftX > contactPoint.x) || (rightX < contactPoint.x))
	{
		return nullptr;
	}

	Physics::Collision* collisionData = new Collision();

	collisionData->collider = other;
	collisionData->contactPoint = contactPoint;

	float colliderAABBMagnitude = (collisionData->contactPoint - position).getMagnitude();
	float penetrationDistance = distance = (other->getRadius() + colliderAABBMagnitude);

	if (penetrationDistance < 0)
		penetrationDistance = -penetrationDistance;

	collisionData->penetrationDistance = penetrationDistance;

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
	GameMath::Vector2 contactSide;
	GameMath::Vector2 contactSideOther;
	GameMath::Vector2 contactCorner;
	GameMath::Vector2 contactCornerOther;
	
	float penetrationDistance;

	if (abs(direction.x) > abs(direction.y))
	{
		if (direction.x < 0)
			normal = GameMath::Vector2(-1, 0);
		else
			normal = GameMath::Vector2(1, 0);

		contactSide = position + (normal * (getWidth() / 2));

		contactSideOther = 
			otherPosition + 
			(
				//direction
				GameMath::Vector2({ -normal.x, -normal.y }) *
				//magnitude
				(other->getWidth() / 2)
			);

		if (normal.y < 0)
		{
			contactCorner = GameMath::Vector2({ contactSide.x, contactSide.y - (getHeight() / 2) });
			contactCornerOther = GameMath::Vector2({ contactSideOther.x, contactSideOther.y + (other->getHeight() / 2) });
		}
		else
		{
			contactCorner = GameMath::Vector2({ contactSide.x, contactSide.y + (getHeight() / 2) });
			contactCornerOther = GameMath::Vector2({ contactSideOther.x, contactSideOther.y - (other->getHeight() / 2) });
		}

		if ((otherPosition.y - contactSide.y) < (otherPosition.y - contactSideOther.y))
			penetrationDistance = (other->getHeight() / 2) - abs(otherPosition.x - contactSide.x);
		else
			penetrationDistance = 0;
	}
	else
	{
		if (direction.y < 0)
			normal = GameMath::Vector2(0, -1);
		else
			normal = GameMath::Vector2(0, 1);

		contactSide = position + (normal * (getHeight() / 2));

		contactSideOther =
			otherPosition +
			(
				//direction
				GameMath::Vector2({ -normal.x, -normal.y }) *
				//magnitude
				(other->getHeight() / 2)
			);

		if (normal.x < 0)
		{
			contactCorner = GameMath::Vector2({ contactSide.x - (getWidth() / 2), contactSide.y });
			contactCornerOther = GameMath::Vector2({ contactSideOther.x + (other->getWidth() / 2) , contactSideOther.y });
		}
		else
		{
			contactCorner = GameMath::Vector2({ contactSide.x + (getWidth() / 2), contactSide.y });
			contactCornerOther = GameMath::Vector2({ contactSideOther.x - (other->getWidth() / 2) , contactSideOther.y });
		}

		if ((otherPosition.x - contactSide.x) < (otherPosition.x - contactSideOther.x))
			penetrationDistance = (other->getWidth() / 2) - abs(otherPosition.x - contactSide.x);
		else
			penetrationDistance = 0;
		
	}

	collisionData->normal = normal;
	collisionData->collider = other;
	collisionData->contactPoint = (contactCornerOther - contactCorner) / 2;
	collisionData->penetrationDistance = penetrationDistance;

	return collisionData;
}

void Physics::AABBColliderComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	float offset = 2.0f;

	RAYLIB_H::DrawRectangleLines(position.x - (m_width / 2) - offset, position.y - (m_height / 2) - offset, m_width + (offset * 2), m_height + (offset * 2), GetColor(getColor()));
}