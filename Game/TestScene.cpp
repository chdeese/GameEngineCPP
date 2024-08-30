#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include <chrono>

void TestScene::onStart()
{
	Engine::Entity* entity = new Engine::Entity();
	entity->getTransform()->setLocalScale({ 100, 100 });
	entity->getTransform()->setLocalPosition({ 400, 400 });

	GameGraphics::ShapeComponent* shape = entity->addComponent<GameGraphics::ShapeComponent>();
	shape->setShapeType(GameGraphics::ShapeType::CIRCLE);
	shape->setColor(0xFF00FFFF);

	 Scene::addEntity(entity);

	 m_entity = entity;
}

void TestScene::onUpdate(double deltaTime)
{
	m_accumulatedTime += deltaTime;

	double circleRadius = 100;
	double speedScale = 0.5;

	GameMath::Vector2 newPosition = { (float)(sin(m_accumulatedTime * 0.5) * circleRadius + 400), (float)(cos(m_accumulatedTime * 0.5) * circleRadius + 400) };
	m_entity->getTransform()->setLocalPosition(newPosition);
}
