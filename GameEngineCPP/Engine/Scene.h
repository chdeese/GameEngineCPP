#pragma once

#include "List.h"

namespace Physics
{
	class Collision;
	class ColliderComponent;
}

namespace Engine
{
	class Entity;

	class Scene
	{
	public:
		Scene();

		void start();
		void update(double deltaTime);
		void fixedUpdate(double fixedDeltaTime);
		void draw();
		void end();

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onFixedUpdate(double deltaTime) {}
		virtual void onDraw() {}
		virtual void onEnd() {}

		void addEntity(Entity* entity);
		void removeEntity(Entity* entity);

		void addActiveCollider(Physics::ColliderComponent* collider) { m_activeColliders.add(collider); }
		void removeActiveCollider(Physics::ColliderComponent* collider) { m_activeColliders.remove(collider); }

	private:
		List<Physics::ColliderComponent*> m_activeColliders;
		List<Entity*> m_entities;
	};
}