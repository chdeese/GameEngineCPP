#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/RigidBodyComponent.h"
#include <chrono>

void TestScene::onStart()
{

	float gravity = 0.01f;


	m_circle1 = new Engine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40, 40 });
	m_circle1->getTransform()->setLocalPosition({ 100,100 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new Physics::CircleColliderComponent(50));

	Physics::RigidBodyComponent* circle1RigidBody = new Physics::RigidBodyComponent();

	circle1RigidBody->setEnabled(true);
	circle1RigidBody->setGravity(gravity);
	circle1RigidBody->setMass(15);

	m_circle1->addComponent(circle1RigidBody);
	
	addEntity(m_circle1);

	m_circle2 = new Engine::Entity();
	m_circle2->getTransform()->setLocalScale({ 40, 40 });
	m_circle2->getTransform()->setLocalPosition({ 600,100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new Physics::CircleColliderComponent(50));

	Physics::RigidBodyComponent* circle2RigidBody = new Physics::RigidBodyComponent();

	circle2RigidBody->setEnabled(true);
	circle2RigidBody->setGravity(gravity);
	circle2RigidBody->setMass(15.0f);

	m_circle2->addComponent(circle2RigidBody);

	addEntity(m_circle2);

	m_floor = new Engine::Entity();
	m_floor->getTransform()->setLocalScale({ 1000, 100 });
	m_floor->getTransform()->setLocalPosition({ 400,750 });
	m_floor->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	addEntity(m_floor);
}

void TestScene::onUpdate(double deltaTime)
{
	GameMath::Vector2 position = m_circle1->getTransform()->getLocalPosition();
	GameMath::Vector2 deltaPosition = { 80, 0 };
	m_circle1->getTransform()->setLocalPosition(position + deltaPosition * deltaTime);
	
}
