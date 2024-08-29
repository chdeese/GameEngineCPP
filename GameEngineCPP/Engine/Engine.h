#pragma once

namespace GameEngine
{
	class Scene;

	class Engine
	{
	public:
		void run();

		static float getDeltaTime() { return m_deltaTime; }

		static void setCurrentScene(Scene* scene) { m_currentScene = scene; }
		static Scene* getCurrentScene() { return m_currentScene; }

		static float getTimeStep() { return m_fixedTimeStep; }
		static void setTimeSet(float time) { m_fixedTimeStep = time; }

	private:
		void start();
		void update(double deltaTime);
		void fixedUpdate();
		void draw();
		void end();

		static Scene* m_currentScene;
		static float m_deltaTime;
		static float m_fixedTimeStep;
	};
}