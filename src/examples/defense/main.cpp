#include <age/core/Parser.h>
#include <age/entity/EntityManager.h>
#include <age/core/Configuration.h>
#include <age/core/Engine.h>
#include <age/graphics/Window.h>
#include <age/core/EngineState.h>
#include <age/graphics/TileMapSystem.h>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;

int main()
{
	const auto engine = std::make_shared<Engine>();
	const auto manager = std::make_shared<EntityManager>(64);
	const auto window = std::make_shared<Window>();
	const auto tileSystem = std::make_shared<TileMapSystem>();
	window->addChild(tileSystem);
	engine->addChild(manager);
	engine->addChild(window);

	if (ReadFile(Configuration::Instance().getPathMaps() / "defense_level1.tmx", manager) == false)
	{
		return EXIT_FAILURE;
	}

	while (engine->getEngineState().getState() < EngineState::State::Exit)
	{
		engine->frame();
	}

	return EXIT_SUCCESS;
}
