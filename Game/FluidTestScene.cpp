#include "FluidTestScene.h"
//FluidParticle includes Entity
#include "Engine/TransformComponent.h"
#include "Graphics/ShapeComponent.h"
#include "Physics/FluidParticle.h"
#include "Physics/AABBColliderComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/RigidBodyComponent.h"
#include "Math/Vector2.h"
#include <cstdlib>
#include <chrono>
#include <iostream>

float FluidTestScene::genRandom()
{
	return ((float)rand() / (RAND_MAX + 1.0f));
}

void FluidTestScene::onStart()
{
	srand(time(0));

	m_floor = new Engine::Entity();
	m_floor->getTransform()->setLocalScale({ 1000, 50 });
	m_floor->getTransform()->setLocalPosition({ 500, 800 });
	m_floor->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_floor->addComponent(new Physics::AABBColliderComponent(1000, 50))->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_floor);

	GameMath::Vector2 scaleTemp;

	m_wall1 = new Engine::Entity();
	scaleTemp = GameMath::Vector2({ 50, 670 });
	m_wall1->getTransform()->setLocalScale(scaleTemp);
	m_wall1->getTransform()->setLocalPosition({ 770, 435 });
	m_wall1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_wall1->addComponent(new Physics::AABBColliderComponent(scaleTemp.x, scaleTemp.y))->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_wall1);


	m_wall2 = new Engine::Entity();
	scaleTemp = GameMath::Vector2({ 50, 670 });
	m_wall2->getTransform()->setLocalScale(scaleTemp);
	m_wall2->getTransform()->setLocalPosition({ 30, 435 });
	m_wall2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);

	m_wall2->addComponent(new Physics::AABBColliderComponent(scaleTemp.x, scaleTemp.y))->setColliderType(Physics::ColliderComponent::ColliderType::AABB);

	addEntity(m_wall2);


	float size = 5;
	float distanceBetweenParticles = 3;

	float mass = 1;
	//spawnFluidParticle(mass, size, {500, 500});

	spawnFluidParticles();
	
}

void FluidTestScene::spawnFluidParticles()
{
	float size = 24;
	float distanceBetweenParticles = 45;

	float mass = 1;
	float fluidStartHeight = m_wall2->getTransform()->getGlobalScale().y;

	//right position of wall1 (x + scale.x)
	float minXPosition = m_wall2->getTransform()->getGlobalPosition().x + (m_wall2->getTransform()->getGlobalScale().x / 2);
	//left position of wall2 (x - scale.x)
	float maxXPosition = m_wall1->getTransform()->getGlobalPosition().x - (m_wall1->getTransform()->getGlobalScale().x / 2);;
	//top position of floor (y - scale.y)
	float maxYPosition = m_floor->getTransform()->getGlobalPosition().y - (m_floor->getTransform()->getGlobalScale().y / 2);

	float spawnBaseX = minXPosition + distanceBetweenParticles * 2;

	GameMath::Vector2 spawnPosition = GameMath::Vector2(spawnBaseX, maxYPosition - fluidStartHeight);

	float particleOffset = (size * 1.5f) + distanceBetweenParticles;


	for (int i = 0; spawnPosition.y + distanceBetweenParticles < maxYPosition; i++)
	{
		std::cout << genRandom() << "\n";

		if (i > 200)
			return;

		spawnFluidParticle(mass, size, spawnPosition);

		//iterate
		spawnPosition.x += particleOffset + (genRandom() - 0.5f);

		if (spawnPosition.x + distanceBetweenParticles < maxXPosition)
			continue;

		spawnPosition.x = spawnBaseX;
		spawnPosition.y += particleOffset;
	}
}

void FluidTestScene::spawnFluidParticle(float mass, float size, GameMath::Vector2 position)
{
	m_currentParticle = new Engine::Entity();

	m_currentParticle->getTransform()->setLocalPosition(position);
	m_currentParticle->getTransform()->setLocalScale({ size, size });

	m_currentParticle->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_currentParticle->addComponent(new Physics::CircleColliderComponent(size))->setColliderType(Physics::ColliderComponent::ColliderType::CIRCLE);
	m_currentParticle->getComponent<Physics::CircleColliderComponent>()->setEnabled(true);


	Physics::RigidBodyComponent* rb = m_currentParticle->addComponent<Physics::RigidBodyComponent>();
	rb->setMass(mass);
	rb->setGravity(9.81f);
	rb->setEnabled(true);

	addEntity(m_currentParticle);
}


