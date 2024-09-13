#pragma once
#include "Engine/Component.h"
#include "Math/Vector2.h"

namespace Physics
{
	class RigidBodyComponent : public Engine::Component
	{
	private:
		GameMath::Vector2 m_velocity;
		float m_mass = 1;
		float m_gravity = 9.81f;

	public:
		GameMath::Vector2 getVelocity() { return m_velocity; }
		void setVelocity(GameMath::Vector2 velocity) { m_velocity = velocity; }

		float getMass() { return m_mass; }
		void setMass(float mass) { m_mass = mass; }

		float getGravity() { return m_gravity; }
		void setGravity(float gravity) { m_gravity = gravity; }

		void applyForce(GameMath::Vector2 force);
		void applyForceToEntity(RigidBodyComponent* rigidbody, GameMath::Vector2 force);

		float dot(GameMath::Vector2 lhs, GameMath::Vector2 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

		void fixedUpdate(float fixedDeltaTime) override;

		void update(double deltaTime) override { };

		void resolveCollision(Physics::Collision* collisionData);

		void onCollisionEnter(Physics::Collision* other) override;
	};
}