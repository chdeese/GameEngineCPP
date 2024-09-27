#include "InputComponent.h"
#include "raylib.h"
#include "Math/Vector2.h"
#include "Entity.h"
#include "Physics/RigidBodyComponent.h"
void Engine::InputComponent::start()
{
	m_rigidBody = getOwner()->getComponent<Physics::RigidBodyComponent>();
}
void Engine::InputComponent::update(double deltaTime)
{
	GameMath::Vector2 delta = GameMath::Vector2({ 0, 0 });

	if (RAYLIB_H::IsKeyDown(KEY_W))
		delta.y--;
	if (RAYLIB_H::IsKeyDown(KEY_S))
		delta.y++;
	if (RAYLIB_H::IsKeyDown(KEY_A))
		delta.x--;
	if (RAYLIB_H::IsKeyDown(KEY_D))
		delta.x++;

	delta.normalize();

	m_rigidBody->applyForce(delta * m_speed * deltaTime);
}
