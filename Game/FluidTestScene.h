#pragma once

#include "Engine/Scene.h"

namespace Engine { class Entity; }
namespace GameMath { class Vector2; }

class FluidTestScene : public Engine::Scene
{
private:
	Engine::Entity* m_wall1;
	Engine::Entity* m_wall2;
	Engine::Entity* m_floor;
	Engine::Entity* m_currentParticle;

	int x;
	float genRandom();

public:
	void onStart() override;

	void spawnFluidParticles();
	void spawnFluidParticle(float mass, float size, GameMath::Vector2 position);
};