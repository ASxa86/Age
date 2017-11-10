#include <examples/pong/Pong.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/entity/EntityManager.h>
#include <age/entity/SystemManager.h>
#include <age/graphics/Window.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/physics/PhysicsSystem.h>
#include <SFML/Graphics.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;
using namespace age::pong;

Pong::Pong() :
	engine{std::make_shared<Engine>()}
{
	auto window = std::make_shared<Window>();
	this->engine->addChild(window);
	auto manager = std::make_shared<EntityManager>();
	this->engine->addChild(manager);

	auto paddle = manager->create();
	paddle.addComponent<int>();
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setPosition(10, 10);
	rec->setSize({ 40, 200 });
	rec->setFillColor(sf::Color::White);
	paddle.addComponent<std::shared_ptr<sf::Drawable>>(rec);

	auto paddle2 = manager->create();
	auto rec2 = std::make_shared<sf::RectangleShape>();
	rec2->setPosition(100, 10);
	rec2->setSize({ 40, 200 });
	rec2->setFillColor(sf::Color::White);
	paddle2.addComponent<std::shared_ptr<sf::Drawable>>(rec2);

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