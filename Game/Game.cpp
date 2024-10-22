#include "Engine/Engine.h"
#include "FluidTestScene.h"

int main(int arc, int argv[])
{
	Engine::Engine engine = Engine::Engine();

	FluidTestScene* scene = new FluidTestScene();

	engine.setCurrentScene(scene);
	engine.run();

	return 0;
}
