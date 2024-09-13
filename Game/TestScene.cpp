#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/AABBColliderComponent.h"
#include <chrono>

void TestScene::onStart()
{
	m_box1 = new Engine::Entity();
	GameMath::Vector2 scale = { 80, 80 };
	m_box1->getTransform()->setLocalScale(scale);
	m_box1->getTransform()->setLocalPosition({ 400 , 100 });
	m_box1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_box1->addComponent(new Physics::AABBColliderComponent(scale.x, scale.y));
	m_box1->getComponent<Physics::AABBColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_box1);





	//m_box2 = new Engine::Entity();
	//GameMath::Vector2 scale2 = { 80, 80 };
	//m_box2->getTransform()->setLocalScale(scale2);
	//m_box2->getTransform()->setLocalPosition({ 100 , 100 });
	//m_box2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	//m_box2->addComponent(new Physics::AABBColliderComponent(scale2.x, scale2.y));
	//m_box2->getComponent<Physics::AABBColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	//addEntity(m_box2);



	m_circle1 = new Engine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40, 40 });
	m_circle1->getTransform()->setLocalPosition({ 100,100 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new Physics::CircleColliderComponent(50));
	m_circle1->getComponent<Physics::CircleColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::CIRCLE);
	addEntity(m_circle1);



	//m_circle2 = new Engine::Entity();
	//m_circle1->getTransform()->setLocalScale({ 40, 40 });
	//m_circle2->getTransform()->setLocalPosition({ 600,100 });
	//m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	//m_circle2->addComponent(new Physics::CircleColliderComponent(50));
	//addEntity(m_circle2);
}

void TestScene::onUpdate(double deltaTime)
{
	GameMath::Vector2 position = m_circle1->getTransform()->getLocalPosition();
	GameMath::Vector2 deltaPosition = { 50, 10 };
	m_circle1->getTransform()->setLocalPosition(position + deltaPosition * deltaTime);
	
}
