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
	Engine::Entity* m_circleStatic;
	Engine::Entity* m_box1;
	Engine::Entity* m_box2;
	Engine::Entity* m_floor;
	Engine::Entity* m_ceiling;
	Engine::Entity* m_wall1;
	Engine::Entity* m_wall2;
};