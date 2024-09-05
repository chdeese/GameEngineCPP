#pragma once

#include "ColliderComponent.h"

namespace Physics
{
	class CircleColliderComponent : public ColliderComponent
	{
	public:
		CircleColliderComponent(float radius) : ColliderComponent() { m_radius = radius; }

		Physics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		Physics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		void draw() override;
		float getRadius() { return m_radius; }
	private:
		float m_radius;
	};
}