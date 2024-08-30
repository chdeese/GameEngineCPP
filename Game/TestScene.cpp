#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"

void TestScene::onStart()
{
	Engine::Entity* entity = new Engine::Entity();
	entity->getTransform()->setLocalScale({ 100, 100 });
	entity->getTransform()->setLocalPosition({ 400, 400 });

	GameGraphics::ShapeComponent* shape = entity->addComponent<GameGraphics::ShapeComponent>();
	shape->setShapeType(GameGraphics::ShapeType::CIRCLE);

	Scene::addEntity(entity);
}
