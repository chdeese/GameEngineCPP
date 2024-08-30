#include "Scene.h"
#include "Entity.h"

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
	for (Entity* entity : m_entities)
	{
		if (!entity->getStarted())
			entity->start();
		entity->update(fixedDeltaTime);
	}
}

void Engine::Scene::draw()
{
	for (Entity* entity : m_entities)
	{
		entity->draw();
	}
	onEnd();
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
