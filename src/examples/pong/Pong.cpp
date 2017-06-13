#include <examples/pong/Pong.h>
#include <examples/pong/Paddle.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/graphics/Window.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/physics/KinematicSystem.h>

using namespace age::core;
using namespace age::pong;

Pong::Pong()
{
	this->engine.addChild(std::make_unique<Paddle>());
	this->engine.addChild(std::make_unique<age::graphics::PlayerInputSystem>());
	this->engine.addChild(std::make_unique<age::physics::KinematicSystem>());
	this->engine.addChild(std::make_unique<age::graphics::Window>());
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