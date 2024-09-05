#pragma once

#include "Engine/Scene.h"
#include "Engine/Entity.h"

class TestScene : public Engine::Scene
{
public: 
	void onStart() override;

	void onUpdate(double deltaTime) override;

private:
	Engine::Entity* m_circle1;
	Engine::Entity* m_circle2;
};