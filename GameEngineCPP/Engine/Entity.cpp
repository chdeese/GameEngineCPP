#include "Entity.h"
#include "Physics/ColliderComponent.h"
#include "TransformComponent.h"

Engine::Entity::Entity()
{
	TransformComponent* transform = new TransformComponent();
	addComponent(transform);
	m_transform = transform;
}

void Engine::Entity::start()
{
	m_started = true;

	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->start();
	}

	onStart();
}

void Engine::Entity::update(double deltaTime)
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->update(deltaTime);
	}

	onUpdate(deltaTime);
}

void Engine::Entity::fixedUpdate(float fixedDeltaTime)
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->fixedUpdate(fixedDeltaTime);
	}

	onFixedUpdate(fixedDeltaTime);
}

void Engine::Entity::draw()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->draw();
	}
}

void Engine::Entity::end()
{
	for (Component* component : m_components)
	{
		component->end();
	}
	m_started = false;
	onEnd();
}

void Engine::Entity::addComponent(Component* component)
{
	component->setOwner(this);
	m_components.add(component);
}

void Engine::Entity::onCollisionEnter(Physics::Collision* collision)
{
	for (Component* component : m_components)
		component->onCollisionEnter(collision);
}

void Engine::Entity::setEnabled(bool enabled)
{
	if (!m_enabled && enabled)
		onEnable();
	else if (m_enabled && !enabled)
		onDisable();

	m_enabled = enabled;
}