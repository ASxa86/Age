#include <examples/pong/Pong.h>
#include <examples/pong/Ball.h>
#include <examples/pong/Paddle.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/graphics/Window.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/physics/KinematicSystem.h>

using namespace age::core;
using namespace age::graphics;
using namespace age::pong;

Pong::Pong()
{
	auto window = std::make_unique<Window>();
	auto player = std::make_unique<Paddle>();
	player->setPosition({50.0, window->getHeight() / 2.0});
	this->engine.addChild(std::move(player));

	auto ai = std::make_unique<Paddle>();
	ai->setPosition({window->getWidth() - 75.0, window->getHeight() / 2.0});
	this->engine.addChild(std::move(ai));

	this->engine.addChild(std::make_unique<Ball>());
	this->engine.addChild(std::make_unique<age::graphics::PlayerInputSystem>());
	this->engine.addChild(std::make_unique<age::physics::KinematicSystem>());
	this->engine.addChild(std::move(window));
	this->engine.setEngineState(EngineState::State::Initialize);
}

Pong::~Pong()
{
}

int Pong::run()
{
	while(this->engine.getEngineState().getState() < EngineState::State::Exit)
	{
		this->engine.frame();
	}

	return 0;
}