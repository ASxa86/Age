#include <azule/core/Configuration.h>
#include <azule/core/Engine.h>
#include <azule/core/EngineState.h>
#include <azule/core/Parser.h>
#include <azule/entity/EntityDatabase.h>

using namespace azule::core;
using namespace azule::entity;

int main()
{
	const auto engine = std::make_unique<Engine>();

	if(ReadFile(Configuration::Instance().getPathData() / "inputs/defense.xml", engine.get()) == false)
	{
		return EXIT_FAILURE;
	}

	auto manager = engine->getChild<EntityDatabase>();

	if(ReadFile(Configuration::Instance().getPathMaps() / "defense_level1.tmx", manager) == false)
	{
		return EXIT_FAILURE;
	}

	engine->setEngineState(azule::core::EngineState::State::StartUp);

	while(engine->getEngineState().getState() < EngineState::State::Shutdown)
	{
		engine->frame();
	}

	return EXIT_SUCCESS;
}