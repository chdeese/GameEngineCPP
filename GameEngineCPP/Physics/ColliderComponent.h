#pragma once

#include "Engine/Component.h"
#include "Math/Vector2.h"

namespace Physics
{
	class CircleColliderComponent;
	class AABBColliderComponent;
	class RigidBodyComponent;

	struct Collision
	{
	public:
		GameMath::Vector2 normal;
		ColliderComponent* collider;
		GameMath::Vector2 contactPoint;
		float penetrationDistance;
	};



	class ColliderComponent : public Engine::Component
	{
	public: 
		enum ColliderType
		{
			CIRCLE,
			AABB
		};

	private:
		bool m_isTrigger;
		ColliderType m_colliderType;
		unsigned int m_color = 0x00FF00FF;
		RigidBodyComponent* m_rigidBody;

	public:
		void start() override;

		Collision* checkCollision(ColliderComponent* other);

		virtual Collision* checkCollisionCircle(CircleColliderComponent* other) = 0;
		virtual Collision* checkCollisionAABB(AABBColliderComponent* other) = 0;

		void onCollisionEnter(Physics::Collision* other) override;

		ColliderType getColliderType() { return m_colliderType; }
		void setColliderType(ColliderType type) { m_colliderType = type; }

		void update(double deltaTime) override;

		unsigned int getColor() { return m_color; }

		bool getIsTrigger() { return m_isTrigger; }
		void setIsTrigger(bool isTrigger) { m_isTrigger = isTrigger; }

		RigidBodyComponent* getRigidBody() { return m_rigidBody; }
	};
}
