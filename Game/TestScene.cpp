#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/AABBColliderComponent.h"
#include "Physics/RigidBodyComponent.h"
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
	Physics::RigidBodyComponent* circle2RigidBody = m_circle2->addComponent(new Physics::RigidBodyComponent());

	circle2RigidBody->setMass(2);
	circle2RigidBody->setGravity(2);
	circle2RigidBody->setEnabled(true);

	addEntity(m_circle2);



	//m_box2 = new Engine::Entity();
	//GameMath::Vector2 scale2 = { 80, 80 };
	//m_box2->getTransform()->setLocalScale(scale2);
	//m_box2->getTransform()->setLocalPosition({ 100 , 100 });
	//m_box2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	//m_box2->addComponent(new Physics::AABBColliderComponent(scale2.x, scale2.y));
	//m_box2->getComponent<Physics::AABBColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::AABB);
	//Physics::RigidBodyComponent* box2RigidBody = m_box2->addComponent(new Physics::RigidBodyComponent());

	//box2RigidBody->setMass(2);
	//box2RigidBody->setGravity(0);
	//box2RigidBody->setEnabled(true);

	//addEntity(m_box2);



	m_circle1 = new Engine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40, 40 });
	m_circle1->getTransform()->setLocalPosition({ 100,100 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new Physics::CircleColliderComponent(42));
	m_circle1->getComponent<Physics::CircleColliderComponent>()->setColliderType(Physics::ColliderComponent::ColliderType::CIRCLE);
	Physics::RigidBodyComponent* circle1RigidBody = m_circle1->addComponent(new Physics::RigidBodyComponent());

	circle1RigidBody->setMass(2);
	circle1RigidBody->setGravity(2);
	circle1RigidBody->setEnabled(true);

	addEntity(m_circle1);


	m_floor = new Engine::Entity();
	m_floor->getTransform()->setLocalScale({1000, 50});
	m_floor->getTransform()->setLocalPosition({500, 500});
	m_floor->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_floor->addComponent(new Physics::AABBColliderComponent(1000, 50)) -> setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_floor);

}

void TestScene::onUpdate(double deltaTime)
{
	GameMath::Vector2 deltaPosition = { 50, 0 };
	m_circle1->getComponent<Physics::RigidBodyComponent>()->applyForce(deltaPosition * deltaTime);

	GameMath::Vector2 deltaPosition2 = { -50, 0 };
	m_circle2->getComponent<Physics::RigidBodyComponent>()->applyForce(deltaPosition2 * deltaTime);
}
