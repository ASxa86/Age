#include <age/core/Configuration.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/Parser.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/graphics/TileMapSystem.h>
#include <age/graphics/Window.h>
#include <iostream>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;

int main()
{
	Engine engine;
	auto manager = engine.addChild<EntityDatabase>();
	auto window = engine.addChild<Window>();
	window->addChild(std::make_unique<TileMapSystem>());

	const auto testTMX = Configuration::Instance().getPathMaps() / "test.tmx";
	if(ReadFile(testTMX, manager) == false)
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
