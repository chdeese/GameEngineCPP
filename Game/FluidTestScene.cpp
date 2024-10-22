#include "FluidTestScene.h"
//FluidParticle includes Entity
#include "Engine/FluidParticle.h"
#include "Engine/TransformComponent.h"
#include "Graphics/ShapeComponent.h"
#include "Physics/AABBColliderComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Math/Vector2.h"

void FluidTestScene::onStart()
{
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

	spawnFluidParticles();
}

void FluidTestScene::onUpdate(double deltaTime)
{
}

void FluidTestScene::spawnFluidParticles()
{
	float size = 20;
	float distanceBetweenParticles = 3;

	float mass = 1;
	float fluidStartHeight = m_wall2->getTransform()->getGlobalScale().y;

	//right position of wall1 (x + scale.x)
	float minXPosition = m_wall2->getTransform()->getGlobalPosition().x + (m_wall2->getTransform()->getGlobalScale().x / 2);
	//left position of wall2 (x - scale.x)
	float maxXPosition = m_wall1->getTransform()->getGlobalPosition().x - (m_wall1->getTransform()->getGlobalScale().x / 2);;
	//top position of floor (y - scale.y)
	float maxYPosition = m_floor->getTransform()->getGlobalPosition().y - (m_floor->getTransform()->getGlobalScale().y / 2);

	GameMath::Vector2 spawnPosition = GameMath::Vector2(minXPosition + distanceBetweenParticles, maxYPosition - fluidStartHeight);
	Engine::FluidParticle* particle;
	
	float particleOffset = (size * 1.5f) + distanceBetweenParticles;

	while (spawnPosition.y + distanceBetweenParticles < maxYPosition)
	{
		particle = new Engine::FluidParticle();
		particle->setMass(mass);
		particle->setSize(size);
		particle->getTransform()->setLocalPosition(spawnPosition);

		addEntity(particle);

		//iterate
		spawnPosition.x += particleOffset;

		if (spawnPosition.x + distanceBetweenParticles < maxXPosition)
			continue;
		
		spawnPosition.x = minXPosition + distanceBetweenParticles;
		spawnPosition.y += particleOffset;
	}
}
