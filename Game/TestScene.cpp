#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include <chrono>

void TestScene::onStart()
{
	m_circle1 = new Engine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40, 40 });
	m_circle1->getTransform()->setLocalPosition({ 100,100 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new Physics::CircleColliderComponent(50));
	addEntity(m_circle1);

	m_circle2 = new Engine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40, 40 });
	m_circle2->getTransform()->setLocalPosition({ 600,100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new Physics::CircleColliderComponent(50));
	addEntity(m_circle2);
}

void TestScene::onUpdate(double deltaTime)
{
	GameMath::Vector2 position = m_circle1->getTransform()->getLocalPosition();
	GameMath::Vector2 deltaPosition = { 20, 0 };
	m_circle1->getTransform()->setLocalPosition(position + deltaPosition * deltaTime);
	
}
