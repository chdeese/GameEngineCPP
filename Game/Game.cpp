#include "Engine/Engine.h"
#include "TestScene.h"

int main(int arc, int argv[])
{
	Engine::Engine engine = Engine::Engine();

	TestScene* scene = new TestScene();

	engine.setCurrentScene(scene);
	engine.run();

	return 0;
}
