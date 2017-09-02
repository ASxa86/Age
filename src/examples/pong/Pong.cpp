#include <examples/pong/Pong.h>
#include <examples/pong/Ball.h>
#include <examples/pong/Paddle.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/graphics/Window.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/physics/PhysicsSystem.h>

using namespace age::core;
using namespace age::graphics;
using namespace age::pong;

Pong::Pong() :
	engine{std::make_shared<Engine>()}
{
	auto window = std::make_shared<Window>();
	auto player = std::make_shared<Paddle>();
	player->setPosition({2.0, 10.0});
	this->engine->addChild(player);

	auto ai = std::make_shared<Paddle>();
	ai->setPosition({36.0, 10.0});
	this->engine->addChild(std::move(ai));

	this->engine->addChild(std::make_shared<Ball>());
	this->engine->addChild(std::make_shared<age::graphics::PlayerInputSystem>());
	this->engine->addChild(std::make_shared<age::physics::PhysicsSystem>());
	this->engine->addChild(window);
	this->engine->setEngineState(EngineState::State::Initialize);
}

Pong::~Pong()
{
}

int Pong::run()
{
	while(this->engine->getEngineState().getState() < EngineState::State::Exit)
	{
		this->engine->frame();
	}

	return 0;
}