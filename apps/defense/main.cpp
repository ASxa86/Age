#include <azule/core/Configuration.h>
#include <azule/core/Engine.h>
#include <azule/core/EngineState.h>
#include <azule/core/Parser.h>
#include <azule/reflection/Properties.h>
#include <azule/core/PluginLoader.h>
#include <azule/entity/EntityDatabase.h>
#include <iostream>

using namespace azule;

int main()
{
	PluginLoader plugins;
	const auto engine = std::make_shared<Engine>();

	if(ReadFile(Configuration::Instance().getPathData() / "inputs/defense.xml", engine.get()) == false)
	{
		return EXIT_FAILURE;
	}

	auto manager = engine->getChild<EntityDatabase>();

	if(ReadFile(Configuration::Instance().getPathMaps() / "defense_level1.tmx", manager.get()) == false)
	{
		return EXIT_FAILURE;
	}

	engine->setEngineState(azule::EngineState::State::StartUp);

	while(engine->getEngineState().getState() < EngineState::State::Shutdown)
	{
		engine->frame();
	}

	return EXIT_SUCCESS;
}
