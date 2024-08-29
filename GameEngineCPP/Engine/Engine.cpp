#include "Engine.h"
#include "Scene.h"
#include "Graphics/Window.h"
#include <chrono>

GameEngine::Scene* GameEngine::Engine::m_currentScene = nullptr;
float GameEngine::Engine::m_fixedTimeStep = 0.02f;
float GameEngine::Engine::m_deltaTime = 0;

void GameEngine::Engine::run()
{
	auto currentTimePoint = std::chrono::high_resolution_clock::now().time_since_epoch();

	double lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint).count();

	double deltaTime = 0; double accumulatedTime = 0;

	GameGraphics::Window window = GameGraphics::Window(800, 800, "Test Application");
	window.open();
	window.setTargetFrameRate(60);

	start();

	while (!window.shouldClose())
	{
		currentTimePoint = std::chrono::high_resolution_clock::now().time_since_epoch();
		double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint).count();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		accumulatedTime += deltaTime / 1000;
		m_deltaTime = deltaTime / 1000;

		update(m_deltaTime);

		while (accumulatedTime >= m_fixedTimeStep)
		{
			accumulatedTime -= m_fixedTimeStep;
			fixedUpdate();
		}

		window.beginDrawing();
		draw();
		window.endDrawing();
	}

	end();
	window.close();
}

void GameEngine::Engine::start()
{
	m_currentScene->start();
}

void GameEngine::Engine::update(double deltaTime)
{
	m_currentScene->update(deltaTime);
}

void GameEngine::Engine::fixedUpdate()
{
	m_currentScene->fixedUpdate(m_fixedTimeStep);
}

void GameEngine::Engine::draw()
{
	m_currentScene->draw();
}

void GameEngine::Engine::end()
{
	m_currentScene->end();
}
