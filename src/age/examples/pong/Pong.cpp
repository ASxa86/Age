#include <age/examples/pong/Pong.h>

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
#include <age/examples/pong/PaddleAIComponent.h>
#include <age/examples/pong/PaddleAISystem.h>
#include <age/graphics/DrawableSystem.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/graphics/TextSystem.h>
#include <age/graphics/Window.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CircleCollisionComponent.h>
#include <age/physics/CollisionEvent.h>
#include <age/physics/EdgeCollisionComponent.h>
#include <age/physics/KinematicComponent.h>
#include <age/physics/PhysicsRenderSystem.h>
#include <age/physics/PhysicsSystem.h>
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

	std::shared_ptr<Engine> engine{std::make_unique<Engine>()};
	sf::SoundBuffer soundBuffer;
	sf::Sound sound{soundBuffer};
	sf::Font font;
};

Pong::Pong()
{
	auto window = this->pimpl->engine->addChild<Window>();
	window->addChild(std::make_unique<DrawableSystem>());
	window->addChild(std::make_unique<TextSystem>());
	window->addChild(std::make_unique<PhysicsRenderSystem>());

	auto manager = this->pimpl->engine->addChild<EntityManager>();
	this->pimpl->engine->addChild(std::make_unique<PlayerInputSystem>());
	this->pimpl->engine->addChild(std::make_unique<AudioSystem>());
	this->pimpl->engine->addChild(std::make_unique<PaddleAISystem>());
	this->pimpl->engine->addChild(std::make_unique<PhysicsSystem>());

	const auto metersW = static_cast<float>(PixelsToMeters(window->getWidth()));
	const auto metersH = static_cast<float>(PixelsToMeters(window->getHeight()));

	// Player 1
	auto paddle = manager->create();
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setSize({1.0, 3.0});
	rec->setFillColor(sf::Color::White);
	rec->setOrigin(rec->getSize().x / 2.0f, rec->getSize().y / 2.0f);
	paddle.addComponent<std::shared_ptr<sf::Drawable>>(rec);

	auto& kinematicP1 = paddle.addComponent<KinematicComponent>();
	kinematicP1.BodyType = KinematicComponent::Type::Kinematic;

	auto& boxColP1 = paddle.addComponent<BoxCollisionComponent>();
	boxColP1.Width = rec->getSize().x;
	boxColP1.Height = rec->getSize().y;

	auto& t = paddle.addComponent<TransformComponent>();
	t.Position = {5, 10};

	auto& input = paddle.addComponent<InputComponent>();
	input.addKeyBinding(sf::Keyboard::Key::Up, [](Entity& e, bool isPressed) {
		auto& k = e.getComponent<KinematicComponent>();
		k.LinearVelocity.Y = isPressed == true ? -20.0f : 0.0f;
	});

	input.addKeyBinding(sf::Keyboard::Key::Down, [](Entity& e, bool isPressed) {
		auto& k = e.getComponent<KinematicComponent>();
		k.LinearVelocity.Y = isPressed == true ? 20.0f : 0.0f;
	});

	// Player 2
	auto paddle2 = manager->create();
	auto& ai = paddle2.addComponent<PaddleAIComponent>();
	auto rec2 = std::make_shared<sf::RectangleShape>();
	rec2->setSize({1.0, 3.0});
	rec2->setFillColor(sf::Color::White);
	rec2->setOrigin(rec2->getSize().x / 2, rec2->getSize().y / 2);
	paddle2.addComponent<std::shared_ptr<sf::Drawable>>(rec2);
	auto& bodyP2 = paddle2.addComponent<KinematicComponent>();
	bodyP2.BodyType = KinematicComponent::Type::Kinematic;

	auto& boxP2 = paddle2.addComponent<BoxCollisionComponent>();
	boxP2.Width = rec2->getSize().x;
	boxP2.Height = rec2->getSize().y;

	auto& t2 = paddle2.addComponent<TransformComponent>();
	t2.Position = {35, 10};

	// Ball
	auto ball = manager->create();
	ai.setBall(ball);
	auto circle = std::make_shared<sf::CircleShape>();
	circle->setRadius(0.5f);
	circle->setFillColor(sf::Color::White);
	circle->setOrigin(circle->getRadius(), circle->getRadius());
	ball.addComponent<std::shared_ptr<sf::Drawable>>(circle);
	ball.addComponent<int>();

	auto& bodyBall = ball.addComponent<KinematicComponent>();
	bodyBall.BodyType = KinematicComponent::Type::Dynamic;
	bodyBall.LinearVelocity = {5.0, 0.0};

	auto& circleP = ball.addComponent<CircleCollisionComponent>();
	circleP.Radius = circle->getRadius();
	circleP.Restitution = 1.0;
	circleP.Friction = 0.0;

	auto& p = ball.addComponent<TransformComponent>();
	p.Position = {10, 10};

	// Top wall
	auto topWall = manager->create();
	topWall.addComponent<TransformComponent>();
	auto& twBody = topWall.addComponent<KinematicComponent>();
	twBody.BodyType = KinematicComponent::Type::Static;

	auto& twEdge = topWall.addComponent<EdgeCollisionComponent>();
	twEdge.Vertex1 = {0.0, 1.0};
	twEdge.Vertex2 = {metersW, 1.0};

	// Bottom wall
	auto bottomWall = manager->create();
	bottomWall.addComponent<TransformComponent>();
	auto& bwBody = bottomWall.addComponent<KinematicComponent>();
	bwBody.BodyType = KinematicComponent::Type::Static;

	auto& bwEdge = bottomWall.addComponent<EdgeCollisionComponent>();
	bwEdge.Vertex1 = {0.0, metersH - 1.0};
	bwEdge.Vertex2 = {metersW, metersH - 1.0};

	// Left Wall
	auto leftWall = manager->create();
	leftWall.addComponent<TransformComponent>();
	auto& lwBody = leftWall.addComponent<KinematicComponent>();
	lwBody.BodyType = KinematicComponent::Type::Static;

	auto& lwEdge = leftWall.addComponent<EdgeCollisionComponent>();
	lwEdge.Vertex1 = {1.0, 0.0};
	lwEdge.Vertex2 = {1.0, metersH};
	lwEdge.IsSensor = true;

	// Right Wall
	auto rightWall = manager->create();
	rightWall.addComponent<TransformComponent>();
	auto& rwBody = rightWall.addComponent<KinematicComponent>();
	rwBody.BodyType = KinematicComponent::Type::Static;

	auto& rwEdge = rightWall.addComponent<EdgeCollisionComponent>();
	rwEdge.Vertex1 = {metersW - 1.0, 0.0};
	rwEdge.Vertex2 = {metersW - 1.0, metersH};
	rwEdge.IsSensor = true;

	// Score 1
	auto score1 = manager->create();
	auto text1 = std::make_shared<sf::Text>();
	text1->setString("0");
	text1->setFont(this->pimpl->font);
	text1->setCharacterSize(60);
	auto tb1 = text1->getLocalBounds();
	text1->setOrigin(tb1.width / 2.0f, tb1.height / 2.0f);
	score1.addComponent<std::shared_ptr<sf::Text>>(text1);
	auto& st1 = score1.addComponent<TransformComponent>();
	st1.Position = {window->getWidth() / 4.0, 100};

	// Score 2
	auto score2 = manager->create();
	auto text2 = std::make_shared<sf::Text>();
	text2->setString("0");
	text2->setFont(this->pimpl->font);
	text2->setCharacterSize(60);
	auto tb2 = text2->getLocalBounds();
	text2->setOrigin(tb2.width / 2.0f, tb2.height / 2.0f);
	score2.addComponent<std::shared_ptr<sf::Text>>(text2);
	auto& st2 = score2.addComponent<TransformComponent>();

	st2.Position = {window->getWidth() - st1.Position.X, 100};

	auto& config = Configuration::Instance();
	this->pimpl->soundBuffer.loadFromFile((config.getPathData() / "audio/ball.wav").string());
	ball.addComponent<sf::Sound>(this->pimpl->soundBuffer);

	// Handle what happens when the ball crosses behind the paddles.
	// Handle playing sounds when the ball collides with the paddles.
	EventQueue::Instance().addEventHandler([=](auto evt) mutable {
		auto evtCollision = dynamic_cast<CollisionEvent*>(evt);

		if(evtCollision != nullptr)
		{
			if(evtCollision->getEntityA() == leftWall || evtCollision->getEntityA() == rightWall)
			{
				auto& t = ball.getComponent<TransformComponent>();
				t.Position = {metersW / 2, metersH / 2};

				auto& b = ball.getComponent<KinematicComponent>();
				b.LinearVelocity = {10.0f, 2.0f};

				if(evtCollision->getEntityA() == leftWall)
				{
					auto& text = score2.getComponent<std::shared_ptr<sf::Text>>();
					auto score = std::stoi(text->getString().toAnsiString());
					text->setString(std::to_string(++score));
				}

				if(evtCollision->getEntityA() == rightWall)
				{
					auto& text = score1.getComponent<std::shared_ptr<sf::Text>>();
					auto score = std::stoi(text->getString().toAnsiString());
					text->setString(std::to_string(++score));
				}
			}
			else
			{
				ball.getComponent<sf::Sound>().play();
				auto v = ball.getComponent<KinematicComponent>().LinearVelocity;
				ball.getComponent<KinematicComponent>().LinearVelocity = {v.X * 1.1f, v.Y * 1.1f};
			}
		}
	});
}

Pong::~Pong()
{
}

int Pong::run()
{
	this->pimpl->engine->setEngineState(EngineState::State::Initialize);

	while(this->pimpl->engine->getEngineState().getState() < EngineState::State::Exit)
	{
		this->pimpl->engine->frame();
	}

	return 0;
}
