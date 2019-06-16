#include <age/core/Configuration.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/Parser.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
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
	const auto engine = std::make_unique<Engine>();
	auto window = engine->addChild<Window>();
	window->addChild(std::make_unique<TileMapSystem>());
	window->addChild(std::make_unique<DrawableSystem>());

	auto manager = engine->addChild<EntityDatabase>();
	engine->addChild(std::make_unique<WaypointSystem>());
	engine->addChild(std::make_unique<PhysicsSystem>());

	if(ReadFile(Configuration::Instance().getPathMaps() / "defense_level1.tmx", manager) == false)
	{
		return EXIT_FAILURE;
	}

	// Enemy
	auto enemy = manager->addEntity();
	auto transform = enemy->addComponent<TransformComponent>();
	transform->Position = {0, 275};

	auto body = enemy->addComponent<KinematicComponent>();
	body->BodyType = KinematicComponent::Type::Kinematic;
	body->LinearVelocity = {50, 0.0};
	body->CalculateHeading = true;

	auto sprite = enemy->addComponent<SpriteComponent>();
	sprite->loadFile(Configuration::Instance().getPathData() / "maps/towerDefense_tilesheet.png");
	sprite->setHFrames(23);
	sprite->setVFrames(13);
	sprite->setFrame(130);
	sprite->Rotation = -90.0;

	auto waypoint = enemy->addComponent<WaypointComponent>();
	waypoint->Waypoints.push_back({{300, 275}});
	waypoint->Waypoints.push_back({{300, 75}});
	waypoint->Waypoints.push_back({{500, 75}});
	waypoint->Waypoints.push_back({{500, 525}});
	waypoint->Waypoints.push_back({{775, 525}});
	waypoint->Waypoints.push_back({{775, 275}});
	waypoint->Waypoints.push_back({{850, 275}});

	engine->setEngineState(age::core::EngineState::State::StartUp);

	while(engine->getEngineState().getState() < EngineState::State::Shutdown)
	{
		engine->frame();
	}

	return EXIT_SUCCESS;
}
