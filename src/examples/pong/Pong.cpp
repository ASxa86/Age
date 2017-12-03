#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/entity/EntityManager.h>
#include <age/entity/SystemManager.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/graphics/Window.h>
#include <age/math/TransformComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <examples/pong/Pong.h>
#include <SFML/Graphics.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::graphics;
using namespace age::pong;

Pong::Pong() : engine{std::make_shared<Engine>()}
{
	auto window = std::make_shared<Window>();
	this->engine->addChild(window);
	auto manager = std::make_shared<EntityManager>();
	this->engine->addChild(manager);
	this->engine->addChild(std::make_shared<PlayerInputSystem>());

	auto paddle = manager->create();
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setSize({40, 200});
	rec->setFillColor(sf::Color::White);
	paddle.addComponent<std::shared_ptr<sf::Drawable>>(rec);
	auto& t = paddle.addComponent<TransformComponent>();
	t.setPosition({10, 10});

	auto& input = paddle.addComponent<InputComponent>();
	input.addKeyBinding(sf::Keyboard::Key::Up, [](Entity e, bool isPressed) {
		if(isPressed == true)
		{
			auto& t = e.getComponent<TransformComponent>();
			auto p = t.getPosition();
			p.setY(p.getY() - 10);
			t.setPosition(p);
		}
	});

	input.addKeyBinding(sf::Keyboard::Key::Down, [](Entity e, bool isPressed) {
		if(isPressed == true)
		{
			auto& t = e.getComponent<TransformComponent>();
			auto p = t.getPosition();
			p.setY(p.getY() + 10);
			t.setPosition(p);
		}
	});

	input.addKeyBinding(sf::Keyboard::Key::Right, [](Entity e, bool isPressed) {
		if(isPressed == true)
		{
			auto& t = e.getComponent<TransformComponent>();
			auto p = t.getPosition();
			p.setX(p.getX() + 10);
			t.setPosition(p);
		}
	});

	input.addKeyBinding(sf::Keyboard::Key::Left, [](Entity e, bool isPressed) {
		if(isPressed == true)
		{
			auto& t = e.getComponent<TransformComponent>();
			auto p = t.getPosition();
			p.setX(p.getX() - 10);
			t.setPosition(p);
		}
	});

	auto paddle2 = manager->create();
	auto rec2 = std::make_shared<sf::RectangleShape>();
	rec2->setSize({40, 200});
	rec2->setFillColor(sf::Color::White);
	paddle2.addComponent<std::shared_ptr<sf::Drawable>>(rec2);
	auto& t2 = paddle2.addComponent<TransformComponent>();
	t2.setPosition({200, 10});

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
