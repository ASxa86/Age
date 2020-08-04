#include <azule/core/Configuration.h>
#include <azule/core/Engine.h>
#include <azule/core/EngineState.h>
#include <azule/core/Parser.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/graphics/TileMapSystem.h>
#include <azule/graphics/Window.h>
#include <iostream>

using namespace azule;
using namespace azule;
using namespace azule;

int main()
{
	Engine engine;
	auto manager = std::make_shared<EntityDatabase>();
	auto window = std::make_shared<Window>();
	window->addChild(std::make_unique<TileMapSystem>());

	engine.addChild(manager);
	engine.addChild(window);

	const auto testTMX = Configuration::Instance().getPathMaps() / "test.tmx";
	if(ReadFile(testTMX, manager.get()) == false)
	{
		std::cerr << "Failed to load " << testTMX << "\n";
	}

	auto state = engine.getEngineState();
	state.setState(EngineState::State::StartUp);
	engine.setEngineState(state);

	while(engine.getEngineState().getState() < EngineState::State::Shutdown)
	{
		engine.frame();
	}

	return 0;
}
