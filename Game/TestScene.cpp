#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/AABBColliderComponent.h"
#include <chrono>

void TestScene::onStart()
{
	//m_box1 = new Engine::Entity();
	//GameMath::Vector2 scale = { 80, 80 };
	//m_box1->getTransform()->setLocalScale(scale);
	//m_box1->getTransform()->setLocalPosition({ 400 , 100 });
	//m_box1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	//m_box1->addComponent(new Physics::AABBColliderComponent(scale.x, scale.y));
	//m_box1->getComponent<Physics::AABBColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	//addEntity(m_box1);


	m_circle2 = new Engine::Entity();
	m_circle2->getTransform()->setLocalScale({ 40, 40 });
	m_circle2->getTransform()->setLocalPosition({ 600,100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new Physics::CircleColliderComponent(42));
	addEntity(m_circle2);



	m_box2 = new Engine::Entity();
	GameMath::Vector2 scale2 = { 80, 80 };
	m_box2->getTransform()->setLocalScale(scale2);
	m_box2->getTransform()->setLocalPosition({ 150 , 300 });
	m_box2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	m_box2->addComponent(new Physics::AABBColliderComponent(scale2.x, scale2.y));
	m_box2->getComponent<Physics::AABBColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::AABB);
	Physics::RigidBodyComponent* box2RigidBody = m_box2->addComponent(new Physics::RigidBodyComponent());

	box2RigidBody->setMass(2);
	box2RigidBody->setGravity(2);
	box2RigidBody->setEnabled(true);

	addEntity(m_box2);



	//m_circle1 = new Engine::Entity();
	//m_circle1->getTransform()->setLocalScale({ 40, 40 });
	//m_circle1->getTransform()->setLocalPosition({ 100,100 });
	//m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	//m_circle1->addComponent(new Physics::CircleColliderComponent(42));
	//m_circle1->getComponent<Physics::CircleColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::CIRCLE);
	//addEntity(m_circle1);


	m_floor = new Engine::Entity();
	m_floor->getTransform()->setLocalScale({1000, 50});
	m_floor->getTransform()->setLocalPosition({500, 800});
	m_floor->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_floor->addComponent(new Physics::AABBColliderComponent(1000, 50)) -> setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_floor);

	m_ceiling = new Engine::Entity();
	m_ceiling->getTransform()->setLocalScale({ 1000, 50 });
	m_ceiling->getTransform()->setLocalPosition({500, 30});
	m_ceiling->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_ceiling->addComponent(new Physics::AABBColliderComponent(1000, 50))->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_ceiling);


	m_wall1 = new Engine::Entity();
	scaleTemp = GameMath::Vector2({ 50, 650 });
	m_wall1->getTransform()->setLocalScale(scaleTemp);
	m_wall1->getTransform()->setLocalPosition({ 770, 400 });
	m_wall1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_wall1->addComponent(new Physics::AABBColliderComponent(scaleTemp.x, scaleTemp.y))->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_wall1);


	m_wall2 = new Engine::Entity();
	scaleTemp = GameMath::Vector2({ 50, 650 });
	m_wall2->getTransform()->setLocalScale(scaleTemp);
	m_wall2->getTransform()->setLocalPosition({ 30, 400 });
	m_wall2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_wall2->addComponent(new Physics::AABBColliderComponent(scaleTemp.x, scaleTemp.y))->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_wall2);

}

void TestScene::onUpdate(double deltaTime)
{
	GameMath::Vector2 position = m_box2->getTransform()->getLocalPosition();
	GameMath::Vector2 deltaPosition = { 50, 0 };
	m_box2->getTransform()->setLocalPosition(position + deltaPosition * deltaTime);
	
}
