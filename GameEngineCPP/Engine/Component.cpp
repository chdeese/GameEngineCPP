#include "Component.h"

void Engine::Component::setEnabled(bool enabled)
{
	if (!m_enabled && enabled)
		onEnable();
	else if (m_enabled && !enabled)
		onDisable();

	m_enabled = enabled;
}

Engine::Entity* Engine::Component::getOwner()
{
	return m_owner;
}

void Engine::Component::setOwner(Entity* entity)
{
	m_owner = entity;
}
