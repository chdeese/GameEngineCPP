#pragma once

#include "Engine/Scene.h"


class Engine::Entity;

class TestScene : public Engine::Scene
{
public: 
	void onStart() override;

	void onUpdate(double deltaTime) override;

private:
	Engine::Entity* m_circle1;
	Engine::Entity* m_circle2;
};