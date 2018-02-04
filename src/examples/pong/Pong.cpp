#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/EventQueue.h>
#include <age/entity/EntityManager.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/graphics/Window.h>
#include <age/math/TransformComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CollisionEvent.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsSystem.h>
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

	// Player 1
	auto paddle = manager->create();
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setSize({1.0, 3.0});
	rec->setFillColor(sf::Color::White);
	rec->setOrigin(rec->getSize().x / 2.0f, rec->getSize().y / 2.0f);
	paddle.addComponent<std::shared_ptr<sf::Drawable>>(rec);
	auto& k = paddle.addComponent<KinematicComponent>();
	k.setBodyType(KinematicComponent::BodyType::Kinematic);
	auto& t = paddle.addComponent<TransformComponent>();
	t.setPosition({5, 10});
	auto& pc = paddle.addComponent<BoxCollisionComponent>();
	pc.setSize({rec->getSize().x, rec->getSize().y});

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

	// Player 2
	auto paddle2 = manager->create();
	auto rec2 = std::make_shared<sf::RectangleShape>();
	rec2->setSize({1.0, 3.0});
	rec2->setFillColor(sf::Color::White);
	rec2->setOrigin(rec2->getSize().x / 2, rec2->getSize().y / 2);
	paddle2.addComponent<std::shared_ptr<sf::Drawable>>(rec2);
	paddle2.addComponent<KinematicComponent>();
	auto& t2 = paddle2.addComponent<TransformComponent>();
	t2.setPosition({35, 10});
	auto& c = paddle2.addComponent<BoxCollisionComponent>();
	c.setSize({rec2->getSize().x, rec2->getSize().y});

	// Ball
	auto ball = manager->create();
	auto circle = std::make_shared<sf::CircleShape>();
	circle->setRadius(0.5f);
	circle->setFillColor(sf::Color::White);
	circle->setOrigin(circle->getRadius(), circle->getRadius());
	ball.addComponent<std::shared_ptr<sf::Drawable>>(circle);
	auto& kb = ball.addComponent<KinematicComponent>();
	kb.setVelocity({5.0, 0.0});
	kb.setBodyType(KinematicComponent::BodyType::Dynamic);
	auto& p = ball.addComponent<TransformComponent>();
	p.setPosition({10, 10});
	auto& cb = ball.addComponent<BoxCollisionComponent>();
	cb.setSize({circle->getRadius() * 2.0f, circle->getRadius() * 2.0f});


	EventQueue::Instance().addEventHandler([paddle, paddle2, ball, &kb](Event* e) {
		auto evt = dynamic_cast<CollisionEvent*>(e);

		if(evt != nullptr)
		{
			const auto& entities = evt->getEntities();

			for(const auto& entity : entities)
			{
				if(entity == ball)
				{
					auto v = kb.getVelocity();
					v.setX(-v.getX());
					kb.setVelocity(v);
				}
			}
		}
	});

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
