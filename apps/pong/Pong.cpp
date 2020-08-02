#include <Pong.h>

#include <PaddleAIComponent.h>
#include <PaddleAISystem.h>
#include <azule/audio/AudioEvent.h>
#include <azule/audio/AudioSystem.h>
#include <azule/core/Configuration.h>
#include <azule/core/Engine.h>
#include <azule/core/EngineState.h>
#include <azule/core/EventQueue.h>
#include <azule/core/Utilities.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <azule/graphics/InputComponent.h>
#include <azule/graphics/PlayerInputSystem.h>
#include <azule/graphics/RenderSystem.h>
#include <azule/graphics/TextSystem.h>
#include <azule/graphics/Window.h>
#include <azule/physics/BoxCollisionComponent.h>
#include <azule/physics/CircleCollisionComponent.h>
#include <azule/physics/CollisionEvent.h>
#include <azule/physics/EdgeCollisionComponent.h>
#include <azule/physics/KinematicComponent.h>
#include <azule/physics/PhysicsRenderSystem.h>
#include <azule/physics/PhysicsSystem.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/utilities/Signal.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace azule;
using namespace azule;
using namespace azule;
using namespace azule;
using namespace azule;
using namespace azule;
using namespace azule::pong;
using namespace azule;

struct Pong::Impl
{
	Impl()
	{
		this->font.loadFromFile((Configuration::Instance().getPathData() / "fonts/sansation.ttf").string());
	}

	std::shared_ptr<Engine> engine{std::make_unique<Engine>()};
	ScopedConnection connection;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound{soundBuffer};
	sf::Font font;
};

Pong::Pong()
{
	auto window = this->pimpl->engine->addChild<Window>();
	window->addChild(std::make_unique<RenderSystem>());
	window->addChild(std::make_unique<TextSystem>());
	window->addChild(std::make_unique<PhysicsRenderSystem>());

	auto manager = this->pimpl->engine->addChild<EntityDatabase>();
	this->pimpl->engine->addChild(std::make_unique<PlayerInputSystem>());
	this->pimpl->engine->addChild(std::make_unique<AudioSystem>());
	this->pimpl->engine->addChild(std::make_unique<PaddleAISystem>());
	this->pimpl->engine->addChild(std::make_unique<PhysicsSystem>());

	const auto metersW = static_cast<float>(PixelsToMeters(window->getWidth()));
	const auto metersH = static_cast<float>(PixelsToMeters(window->getHeight()));

	// Player 1
	auto paddle = manager->addEntity();
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setSize({1.0, 3.0});
	rec->setFillColor(sf::Color::White);
	rec->setOrigin(rec->getSize().x / 2.0f, rec->getSize().y / 2.0f);
	// paddle->addComponent<std::shared_ptr<sf::Drawable>>(rec);

	auto kinematicP1 = paddle->addComponent<KinematicComponent>();
	kinematicP1->BodyType = KinematicComponent::Type::Kinematic;

	auto boxColP1 = paddle->addComponent<BoxCollisionComponent>();
	boxColP1->Width = rec->getSize().x;
	boxColP1->Height = rec->getSize().y;

	auto t = paddle->addComponent<TransformComponent>();
	t->Position = {5, 10};

	auto input = paddle->addComponent<InputComponent>();
	input->addKeyBinding(sf::Keyboard::Key::Up, [](Entity& e, bool isPressed) {
		auto k = e.getChild<KinematicComponent>();
		k->LinearVelocity.y = isPressed == true ? -20.0f : 0.0f;
	});

	input->addKeyBinding(sf::Keyboard::Key::Down, [](Entity& e, bool isPressed) {
		auto k = e.getChild<KinematicComponent>();
		k->LinearVelocity.y = isPressed == true ? 20.0f : 0.0f;
	});

	// Player 2
	auto paddle2 = manager->addEntity();
	auto ai = paddle2->addComponent<PaddleAIComponent>();
	(void)ai;
	auto rec2 = std::make_shared<sf::RectangleShape>();
	rec2->setSize({1.0, 3.0});
	rec2->setFillColor(sf::Color::White);
	rec2->setOrigin(rec2->getSize().x / 2, rec2->getSize().y / 2);
	// paddle2->addComponent<std::shared_ptr<sf::Drawable>>(rec2);
	auto bodyP2 = paddle2->addComponent<KinematicComponent>();
	bodyP2->BodyType = KinematicComponent::Type::Kinematic;

	auto boxP2 = paddle2->addComponent<BoxCollisionComponent>();
	boxP2->Width = rec2->getSize().x;
	boxP2->Height = rec2->getSize().y;

	auto t2 = paddle2->addComponent<TransformComponent>();
	t2->Position = {35, 10};

	// Ball
	auto ball = manager->addEntity();
	// ai->setBall(*ball);
	auto circle = std::make_shared<sf::CircleShape>();
	circle->setRadius(0.5f);
	circle->setFillColor(sf::Color::White);
	circle->setOrigin(circle->getRadius(), circle->getRadius());
	// ball->addComponent<std::shared_ptr<sf::Drawable>>(circle);

	auto bodyBall = ball->addComponent<KinematicComponent>();
	bodyBall->BodyType = KinematicComponent::Type::Dynamic;
	bodyBall->LinearVelocity = {5.0, 0.0};

	auto circleP = ball->addComponent<CircleCollisionComponent>();
	circleP->Radius = circle->getRadius();
	circleP->Restitution = 1.0;
	circleP->Friction = 0.0;

	auto p = ball->addComponent<TransformComponent>();
	p->Position = {10, 10};

	// Top wall
	auto topWall = manager->addEntity();
	topWall->addComponent<TransformComponent>();
	auto twBody = topWall->addComponent<KinematicComponent>();
	twBody->BodyType = KinematicComponent::Type::Static;

	auto twEdge = topWall->addComponent<EdgeCollisionComponent>();
	twEdge->Vertex1 = {0.0, 1.0};
	twEdge->Vertex2 = {metersW, 1.0};

	// Bottom wall
	auto bottomWall = manager->addEntity();
	bottomWall->addComponent<TransformComponent>();
	auto bwBody = bottomWall->addComponent<KinematicComponent>();
	bwBody->BodyType = KinematicComponent::Type::Static;

	auto bwEdge = bottomWall->addComponent<EdgeCollisionComponent>();
	bwEdge->Vertex1 = {0.0, metersH - 1.0};
	bwEdge->Vertex2 = {metersW, metersH - 1.0};

	// Left Wall
	auto leftWall = manager->addEntity();
	leftWall->addComponent<TransformComponent>();
	auto lwBody = leftWall->addComponent<KinematicComponent>();
	lwBody->BodyType = KinematicComponent::Type::Static;

	auto lwEdge = leftWall->addComponent<EdgeCollisionComponent>();
	lwEdge->Vertex1 = {1.0, 0.0};
	lwEdge->Vertex2 = {1.0, metersH};
	lwEdge->IsSensor = true;

	// Right Wall
	auto rightWall = manager->addEntity();
	rightWall->addComponent<TransformComponent>();
	auto rwBody = rightWall->addComponent<KinematicComponent>();
	rwBody->BodyType = KinematicComponent::Type::Static;

	auto rwEdge = rightWall->addComponent<EdgeCollisionComponent>();
	rwEdge->Vertex1 = {metersW - 1.0, 0.0};
	rwEdge->Vertex2 = {metersW - 1.0, metersH};
	rwEdge->IsSensor = true;

	// Score 1
	auto score1 = manager->addEntity();
	auto text1 = std::make_shared<sf::Text>();
	text1->setString("0");
	text1->setFont(this->pimpl->font);
	text1->setCharacterSize(60);
	auto tb1 = text1->getLocalBounds();
	text1->setOrigin(tb1.width / 2.0f, tb1.height / 2.0f);
	// score1->addComponent<std::shared_ptr<sf::Text>>(text1);
	auto st1 = score1->addComponent<TransformComponent>();
	st1->Position = {window->getWidth() / 4.0, 100};

	// Score 2
	auto score2 = manager->addEntity();
	auto text2 = std::make_shared<sf::Text>();
	text2->setString("0");
	text2->setFont(this->pimpl->font);
	text2->setCharacterSize(60);
	auto tb2 = text2->getLocalBounds();
	text2->setOrigin(tb2.width / 2.0f, tb2.height / 2.0f);
	// score2->addComponent<std::shared_ptr<sf::Text>>(text2);
	auto st2 = score2->addComponent<TransformComponent>();

	st2->Position = {window->getWidth() - st1->Position.y, 100};

	auto& config = Configuration::Instance();
	this->pimpl->soundBuffer.loadFromFile((config.getPathData() / "audio/ball.wav").string());
	// ball->addComponent<sf::Sound>(this->pimpl->soundBuffer);

	// Handle what happens when the ball crosses behind the paddles.
	// Handle playing sounds when the ball collides with the paddles.
	this->pimpl->connection = EventQueue::Instance().addEventHandler([=](auto evt) mutable {
		auto evtCollision = dynamic_cast<CollisionEvent*>(evt);

		if(evtCollision != nullptr)
		{
			// if(evtCollision->getEntityA() == leftWall || evtCollision->getEntityA() == rightWall)
			{
				auto t = ball->getChild<TransformComponent>();
				t->Position = {metersW / 2, metersH / 2};

				auto b = ball->getChild<KinematicComponent>();
				b->LinearVelocity = {10.0f, 2.0f};

				// if(evtCollision->getEntityA() == leftWall)
				{
					// auto text = *score2->getChild<std::shared_ptr<sf::Text>>();
					// auto score = std::stoi(text->getString().toAnsiString());
					// text->setString(std::to_string(++score));
				}

				// if(evtCollision->getEntityA() == rightWall)
				{
					// auto text = *score1->getChild<std::shared_ptr<sf::Text>>();
					// auto score = std::stoi(text->getString().toAnsiString());
					// text->setString(std::to_string(++score));
				}
			}
			// else
			{
				// ball->getChild<sf::Sound>()->play();
				auto v = ball->getChild<KinematicComponent>()->LinearVelocity;
				ball->getChild<KinematicComponent>()->LinearVelocity = {v.x * 1.1f, v.y * 1.1f};
			}
		}
	});
}

Pong::~Pong()
{
}

int Pong::run()
{
	this->pimpl->engine->setEngineState(EngineState::State::StartUp);

	while(this->pimpl->engine->getEngineState().getState() < EngineState::State::Shutdown)
	{
		this->pimpl->engine->frame();
	}

	return 0;
}