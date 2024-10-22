#include "FluidParticle.h"
#include "TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/RigidBodyComponent.h"
#include "Graphics/ShapeComponent.h"

void Engine::FluidParticle::onStart()
{
	addComponent(new Physics::CircleColliderComponent(m_size / 2));
	getTransform()->setLocalScale({ m_size, m_size });
	addComponent<Physics::RigidBodyComponent>();
	getComponent<Physics::RigidBodyComponent>()->setMass(m_mass);
	addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
}
void Engine::FluidParticle::onUpdate(double deltaTime)
{

}
