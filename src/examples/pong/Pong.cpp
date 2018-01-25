#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/entity/EntityManager.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/graphics/Window.h>
#include <age/math/TransformComponent.h>
#include <age/physics/PhysicsSystem.h>
#include <age/physics/KinematicComponent.h>
#include <examples/pong/Pong.h>
#include <SFML/Graphics.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::graphics;
using namespace age::physics;
using namespace age::pong;

Pong::Pong() : engine{std::make_shared<Engine>()}
{
	auto window = std::make_shared<Window>();
	this->engine->addChild(window);
	auto manager = std::make_shared<EntityManager>();
	this->engine->addChild(manager);
	this->engine->addChild(std::make_shared<PlayerInputSystem>());
	this->engine->addChild(std::make_shared<PhysicsSystem>());

	auto paddle = manager->create();
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setSize({1.0, 3.0});
	rec->setFillColor(sf::Color::White);
	paddle.addComponent<std::shared_ptr<sf::Drawable>>(rec);
	paddle.addComponent<KinematicComponent>();
	auto& t = paddle.addComponent<TransformComponent>();
	t.setPosition({10, 10});

	auto& input = paddle.addComponent<InputComponent>();
	input.addKeyBinding(sf::Keyboard::Key::Up, [](Entity e, bool isPressed) {
		auto& t = e.getComponent<KinematicComponent>();
		auto v = t.getVelocity();
		v.setY(isPressed == true ? -20.0 : 0.0);
		t.setVelocity(v);
	});

	input.addKeyBinding(sf::Keyboard::Key::Down, [](Entity e, bool isPressed) {
		auto& t = e.getComponent<KinematicComponent>();
		auto v = t.getVelocity();
		v.setY(isPressed == true ? 20.0 : 0.0);
		t.setVelocity(v);
	});

	input.addKeyBinding(sf::Keyboard::Key::Right, [](Entity e, bool isPressed) {
		auto& t = e.getComponent<KinematicComponent>();
		auto v = t.getVelocity();
		v.setX(isPressed == true ? 20.0 : 0.0);
		t.setVelocity(v);
	});

	input.addKeyBinding(sf::Keyboard::Key::Left, [](Entity e, bool isPressed) {
		auto& t = e.getComponent<KinematicComponent>();
		auto v = t.getVelocity();
		v.setX(isPressed == true ? -20.0 : 0.0);
		t.setVelocity(v);
	});

	auto paddle2 = manager->create();
	auto rec2 = std::make_shared<sf::RectangleShape>();
	rec2->setSize({1.0, 3.0});
	rec2->setFillColor(sf::Color::White);
	paddle2.addComponent<std::shared_ptr<sf::Drawable>>(rec2);
	paddle2.addComponent<KinematicComponent>();
	auto& t2 = paddle2.addComponent<TransformComponent>();
	t2.setPosition({20, 10});

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
