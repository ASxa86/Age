#include <age/core/Configuration.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/Parser.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/graphics/DrawableSystem.h>
#include <age/graphics/SpriteComponent.h>
#include <age/graphics/TileMapSystem.h>
#include <age/graphics/Window.h>
#include <age/navigation/WaypointComponent.h>
#include <age/navigation/WaypointSystem.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <iostream>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;
using namespace age::navigation;
using namespace age::physics;

int main()
{
	const auto engine = std::make_shared<Engine>();
	const auto manager = std::make_shared<EntityManager>(10);
	const auto window = std::make_shared<Window>();
	window->addChild(std::make_shared<TileMapSystem>());
	window->addChild(std::make_shared<DrawableSystem>());
	engine->addChild(manager);
	engine->addChild(window);
	engine->addChild(std::make_shared<WaypointSystem>());

	auto physics = std::make_shared<PhysicsSystem>();
	engine->addChild(physics);

	if(ReadFile(Configuration::Instance().getPathMaps() / "defense_level1.tmx", manager) == false)
	{
		return EXIT_FAILURE;
	}

	// Enemy
	auto enemy = manager->create();
	auto& transform = enemy.addComponent<TransformComponent>();
	transform.setPosition({0, 275});

	auto& body = enemy.addComponent<KinematicComponent>();
	body.BodyType = KinematicComponent::BodyType::Kinematic;
	body.LinearVelocity = {100.0, 0.0};
	// body.CalculateHeading = true;

	auto& sprite = enemy.addComponent<SpriteComponent>();
	sprite.loadFile(Configuration::Instance().getPathData() / "characters/Filga_1.png");
	sprite.setHFrames(4);
	sprite.setVFrames(4);
	sprite.setFrame(0);

	auto& waypoint = enemy.addComponent<WaypointComponent>();
	waypoint.Waypoints.push_back({{300, 275}});
	waypoint.Waypoints.push_back({{300, 75}});
	waypoint.Waypoints.push_back({{500, 75}});
	waypoint.Waypoints.push_back({{500, 525}});
	waypoint.Waypoints.push_back({{775, 525}});
	waypoint.Waypoints.push_back({{775, 275}});
	waypoint.Waypoints.push_back({{850, 275}});

	engine->setEngineState(age::core::EngineState::State::Initialize);

	while(engine->getEngineState().getState() < EngineState::State::Exit)
	{
		engine->frame();
	}

	return EXIT_SUCCESS;
}
