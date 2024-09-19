#include "Scene.h"
#include "Entity.h"
#include "Physics/ColliderComponent.h"
#include "Physics/RigidBodyComponent.h"

Engine::Scene::Scene()
{
	m_entities = List<Entity*>();
}

void Engine::Scene::start()
{
	for (Entity* entity : m_entities)
	{
		entity->start();
	}
	onStart();
}

void Engine::Scene::update(double deltaTime)
{
	for (Entity* entity : m_entities)
	{
		if (!entity->getStarted())
			entity->start();

		entity->update(deltaTime);
	}

	onUpdate(deltaTime);
}

void Engine::Scene::fixedUpdate(double fixedDeltaTime)
{
	// Update Entities
	for (Entity* entity : m_entities)
	{
		if (!entity->getStarted())
			entity->start();
		entity->fixedUpdate(fixedDeltaTime);
	}

	onFixedUpdate(fixedDeltaTime);

	// Update Colliders
	for (auto row = m_activeColliders.begin(); row != m_activeColliders.end(); row++)
	{
		for (auto column = row; column != m_activeColliders.end(); column++)
		{
			if (row == column)
				continue;


			Physics::Collision* collisionData1 = nullptr;
			Physics::Collision* collisionData2 = new Physics::Collision();
			Physics::ColliderComponent* collider1 = *row;
			Physics::ColliderComponent* collider2 = *column;

			if (collisionData1 = collider1->checkCollision(collider2))
			{
				// Get collider 1 rigidbody and resolve collision

				collider1->getOwner()->onCollisionEnter(collisionData1);

				collisionData2->collider = collider1;
				collisionData2->penetrationDistance = collisionData1->penetrationDistance;
				collisionData2->normal = collisionData1->normal * -1;
				collisionData2->contactPoint = collisionData1->contactPoint;
				collider2->getOwner()->onCollisionEnter(collisionData2);


				collider1->getRigidBody()->resolveCollision(collisionData1);
			}
		}
	}
}

void Engine::Scene::draw()
{
	for (Entity* entity : m_entities)
	{
		entity->draw();
	}
	onDraw();
}

void Engine::Scene::end()
{
	for (Entity* entity : m_entities)
	{
		entity->end();
	}
	onEnd();
}

void Engine::Scene::addEntity(Entity* entity)
{
	m_entities.add(entity);
}

void Engine::Scene::removeEntity(Entity* entity)
{
	m_entities.remove(entity);
}
