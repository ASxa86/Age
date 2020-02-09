#include <age/core/Configuration.h>
#include <age/core/Engine.h>
#include <age/core/Factory.h>
#include <age/core/EngineState.h>
#include <age/core/Parser.h>
#include <age/entity/EntityDatabase.h>

using namespace age::core;
using namespace age::entity;

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

	engine->setEngineState(age::core::EngineState::State::StartUp);

	while(engine->getEngineState().getState() < EngineState::State::Shutdown)
	{
		engine->frame();
	}

	return EXIT_SUCCESS;
}