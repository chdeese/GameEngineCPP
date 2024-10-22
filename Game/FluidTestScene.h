#pragma once

#include "Engine/Scene.h"

namespace Engine { class Entity; }

class FluidTestScene : public Engine::Scene
{
private:
	Engine::Entity* m_wall1;
	Engine::Entity* m_wall2;
	Engine::Entity* m_floor;
public:
	void onStart() override;
	void onUpdate(double deltaTime) override;

	void spawnFluidParticles();
};