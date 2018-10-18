#include <examples/pong/Pong.h>

#include <Box2D/Box2D.h>
#include <age/audio/AudioEvent.h>
#include <age/audio/AudioSystem.h>
#include <age/core/Configuration.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/core/Utilities.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/graphics/DrawableSystem.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/graphics/TextSystem.h>
#include <age/graphics/Window.h>
#include <age/physics/BodyComponent.h>
#include <age/physics/CollisionEvent.h>
#include <age/physics/PhysicsRenderSystem.h>
#include <age/physics/PhysicsSystem.h>
#include <examples/pong/PaddleAIComponent.h>
#include <examples/pong/PaddleAISystem.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace age::audio;
using namespace age::core;
using namespace age::entity;
using namespace age::math;
using namespace age::graphics;
using namespace age::physics;
using namespace age::pong;

struct Pong::Impl
{
	Impl()
	{
		this->font.loadFromFile((Configuration::Instance().getPathData() / "fonts/sansation.ttf").string());
	}

	std::shared_ptr<Engine> engine{std::make_shared<Engine>()};
	sf::SoundBuffer soundBuffer;
	sf::Sound sound{soundBuffer};
	sf::Font font;
};

Pong::Pong()
{
	auto& config = Configuration::Instance();
	auto window = std::make_shared<Window>();
	window->addChild(std::make_shared<DrawableSystem>());
	window->addChild(std::make_shared<TextSystem>());
	window->addChild(std::make_shared<PhysicsRenderSystem>());
	this->pimpl->engine->addChild(window);
	auto manager = std::make_shared<EntityManager>();
	this->pimpl->engine->addChild(manager);
	this->pimpl->engine->addChild(std::make_shared<PlayerInputSystem>());
	this->pimpl->engine->addChild(std::make_shared<AudioSystem>());
	this->pimpl->engine->addChild(std::make_shared<PaddleAISystem>());

	auto physics = std::make_shared<PhysicsSystem>();
	this->pimpl->engine->addChild(physics);

	const auto metersW = static_cast<float>(PixelsToMeters(window->getWidth()));
	const auto metersH = static_cast<float>(PixelsToMeters(window->getHeight()));

	// Player 1
	auto paddle = manager->create();
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setSize({1.0, 3.0});
	rec->setFillColor(sf::Color::White);
	rec->setOrigin(rec->getSize().x / 2.0f, rec->getSize().y / 2.0f);
	paddle->addComponent<std::shared_ptr<sf::Drawable>>(rec);

	auto& bodyP1 = paddle->addComponent<BodyComponent>(*physics, paddle);
	bodyP1.body->SetType(b2BodyType::b2_kinematicBody);
	b2PolygonShape rectShape;
	rectShape.SetAsBox(rec->getSize().x / 2.0f, rec->getSize().y / 2.0f);
	b2FixtureDef p1fdef;
	p1fdef.shape = &rectShape;
	bodyP1.body->CreateFixture(&p1fdef);

	auto& t = paddle->addComponent<TransformComponent>();
	t.setPosition({5, 10});

	auto& input = paddle->addComponent<InputComponent>();
	input.addKeyBinding(sf::Keyboard::Key::Up, [](Entity& e, bool isPressed) {
		auto& t = e.getComponent<BodyComponent>();
		auto v = t.body->GetLinearVelocity();
		v.y = isPressed == true ? -20.0f : 0.0f;
		t.body->SetLinearVelocity(v);
	});

	input.addKeyBinding(sf::Keyboard::Key::Down, [](Entity& e, bool isPressed) {
		auto& t = e.getComponent<BodyComponent>();
		auto v = t.body->GetLinearVelocity();
		v.y = isPressed == true ? 20.0f : 0.0f;
		t.body->SetLinearVelocity(v);
	});

	// Player 2
	auto paddle2 = manager->create();
	auto& ai = paddle2->addComponent<PaddleAIComponent>();
	auto rec2 = std::make_shared<sf::RectangleShape>();
	rec2->setSize({1.0, 3.0});
	rec2->setFillColor(sf::Color::White);
	rec2->setOrigin(rec2->getSize().x / 2, rec2->getSize().y / 2);
	paddle2->addComponent<std::shared_ptr<sf::Drawable>>(rec2);
	auto& bodyP2 = paddle2->addComponent<BodyComponent>(*physics, paddle2);
	bodyP2.body->SetType(b2BodyType::b2_kinematicBody);
	b2PolygonShape rectShape2;
	rectShape2.SetAsBox(rec2->getSize().x / 2.0f, rec2->getSize().y / 2.0f);
	b2FixtureDef p2fdef;
	p2fdef.shape = &rectShape2;
	bodyP2.body->CreateFixture(&p2fdef);

	auto& t2 = paddle2->addComponent<TransformComponent>();
	t2.setPosition({35, 10});

	// Ball
	auto ball = manager->create();
	ai.setBall(ball);
	auto circle = std::make_shared<sf::CircleShape>();
	circle->setRadius(0.5f);
	circle->setFillColor(sf::Color::White);
	circle->setOrigin(circle->getRadius(), circle->getRadius());
	ball->addComponent<std::shared_ptr<sf::Drawable>>(circle);
	ball->addComponent<int>();

	auto& bodyBall = ball->addComponent<BodyComponent>(*physics, ball);
	bodyBall.body->SetType(b2BodyType::b2_dynamicBody);
	bodyBall.body->SetLinearVelocity({5.0f, 0.0f});

	b2FixtureDef fdef;
	b2CircleShape shapeCircle;
	shapeCircle.m_radius = circle->getRadius();
	fdef.shape = &shapeCircle;
	fdef.restitution = 1.0;
	fdef.friction = 0.0;
	bodyBall.body->CreateFixture(&fdef);

	auto& p = ball->addComponent<TransformComponent>();
	p.setPosition({10, 10});

	// Top wall
	auto topWall = manager->create();
	auto& twBody = topWall->addComponent<BodyComponent>(*physics, topWall);
	twBody.body->SetType(b2BodyType::b2_staticBody);

	b2EdgeShape twEdge;
	twEdge.Set({0.0f, 0.0f}, {static_cast<float32>(PixelsToMeters(window->getWidth())), 0.0f});
	b2FixtureDef twfdef;
	twfdef.shape = &twEdge;
	twBody.body->CreateFixture(&twfdef);

	// Bottom wall
	auto bottomWall = manager->create();
	auto& bwBody = bottomWall->addComponent<BodyComponent>(*physics, bottomWall);
	bwBody.body->SetType(b2BodyType::b2_staticBody);

	b2EdgeShape bwEdge;
	bwEdge.Set({0.0f, metersH}, {metersW, metersH});
	b2FixtureDef bwfdef;
	bwfdef.shape = &bwEdge;
	bwBody.body->CreateFixture(&bwfdef);

	// Left Wall
	auto leftWall = manager->create();
	auto& lwBody = leftWall->addComponent<BodyComponent>(*physics, leftWall);
	lwBody.body->SetType(b2BodyType::b2_staticBody);

	b2EdgeShape lwEdge;
	lwEdge.Set({1.0f, 0.0f}, {1.0f, metersH});
	b2FixtureDef lwfdef;
	lwfdef.shape = &lwEdge;
	auto lf = lwBody.body->CreateFixture(&lwfdef);
	lf->SetSensor(true);

	// Right Wall
	auto rightWall = manager->create();
	auto& rwBody = rightWall->addComponent<BodyComponent>(*physics, rightWall);
	rwBody.body->SetType(b2BodyType::b2_staticBody);

	b2EdgeShape rwEdge;
	rwEdge.Set({metersW - 1.0f, 0.0f}, {metersW - 1.0f, metersH});
	b2FixtureDef rwfdef;
	rwfdef.shape = &rwEdge;
	auto rf = rwBody.body->CreateFixture(&rwfdef);
	rf->SetSensor(true);

	// Score 1
	auto score1 = manager->create();
	auto text1 = std::make_shared<sf::Text>();
	text1->setString("0");
	text1->setFont(this->pimpl->font);
	text1->setCharacterSize(60);
	auto tb1 = text1->getLocalBounds();
	text1->setOrigin(tb1.width / 2.0f, tb1.height / 2.0f);
	score1->addComponent<std::shared_ptr<sf::Text>>(text1);
	auto& st1 = score1->addComponent<TransformComponent>();
	st1.setPosition({window->getWidth() / 4.0, 100});

	// Score 2
	auto score2 = manager->create();
	auto text2 = std::make_shared<sf::Text>();
	text2->setString("0");
	text2->setFont(this->pimpl->font);
	text2->setCharacterSize(60);
	auto tb2 = text2->getLocalBounds();
	text2->setOrigin(tb2.width / 2.0f, tb2.height / 2.0f);
	score2->addComponent<std::shared_ptr<sf::Text>>(text2);
	auto& st2 = score2->addComponent<TransformComponent>();

	st2.setPosition({window->getWidth() - st1.getPosition().getX(), 100});

	this->pimpl->soundBuffer.loadFromFile((config.getPathData() / "audio/ball.wav").string());
	ball->addComponent<sf::Sound>(this->pimpl->soundBuffer);

	EventQueue::Instance().addEventHandler([=](auto evt) mutable {
		auto evtCollision = dynamic_cast<CollisionEvent*>(evt);

		if(evtCollision != nullptr)
		{
			if(evtCollision->getEntityA() == leftWall || evtCollision->getEntityA() == rightWall)
			{
				auto& t = ball->getComponent<TransformComponent>();
				t.setPosition({metersW / 2, metersH / 2});

				auto& b = ball->getComponent<BodyComponent>();
				b.body->SetLinearVelocity({10.0f, 2.0f});

				if(evtCollision->getEntityA() == leftWall)
				{
					auto& text = score2->getComponent<std::shared_ptr<sf::Text>>();
					auto score = std::stoi(text->getString().toAnsiString());
					text->setString(std::to_string(++score));
				}

				if(evtCollision->getEntityA() == rightWall)
				{
					auto& text = score1->getComponent<std::shared_ptr<sf::Text>>();
					auto score = std::stoi(text->getString().toAnsiString());
					text->setString(std::to_string(++score));
				}
			}
			else
			{
				ball->getComponent<sf::Sound>().play();
				auto v = ball->getComponent<BodyComponent>().body->GetLinearVelocity();
				ball->getComponent<BodyComponent>().body->SetLinearVelocity({v.x * 1.1f, v.y * 1.1f});
			}
		}
	});

	this->pimpl->engine->setEngineState(EngineState::State::Initialize);
}

Pong::~Pong()
{
}

int Pong::run()
{
	while(this->pimpl->engine->getEngineState().getState() < EngineState::State::Exit)
	{
		this->pimpl->engine->frame();
	}

	return 0;
}
