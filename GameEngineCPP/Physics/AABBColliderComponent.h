#pragma once

#include "ColliderComponent.h"

namespace Physics
{
	class AABBColliderComponent : public ColliderComponent
	{
	private:
		float m_width;
		float m_height;
	public:
		AABBColliderComponent(float width, float height) : ColliderComponent() { m_width = width; m_height = height; }

		Physics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		Physics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		void draw() override;
		 
		float getWidth() { return m_width; }
		float getHeight() { return m_height; }

		float dot(GameMath::Vector2 lhs, GameMath::Vector2 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
		float abs(float number) { if (number < 0) return -number; else return number; }
	};
}