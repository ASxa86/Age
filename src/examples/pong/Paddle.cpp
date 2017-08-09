#include <examples/pong/Paddle.h>
#include <age/graphics/RectangleComponent.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/Command.h>
#include <age/math/TransformComponent.h>
#include <age/physics/KinematicComponent.h>

using namespace age::core;
using namespace age::graphics;
using namespace age::math;
using namespace age::physics;
using namespace age::pong;

class MoveUp : public age::graphics::Command
{
public:
	MoveUp() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Up);
	}

	void execute(age::core::Entity* x, bool keyPressed) override
	{
		auto component = x->getChild<KinematicComponent>();
		auto v = component->getVelocity();
		v.y() = keyPressed == true ? -500.0 : 0.0;
		component->setVelocity(v);
	}
};

class MoveDown : public age::graphics::Command
{
public:
	MoveDown() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Down);
	}

	void execute(age::core::Entity* x, bool keyPressed) override
	{
		auto component = x->getChild<KinematicComponent>();
		auto v = component->getVelocity();
		v.y() = keyPressed == true ? 500.0 : 0.0;
		component->setVelocity(v);
	}
};

class MoveRight : public age::graphics::Command
{
public:
	MoveRight() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Right);
	}

	void execute(age::core::Entity* x, bool keyPressed) override
	{
		auto component = x->getChild<KinematicComponent>();
		auto v = component->getVelocity();
		v.x() = keyPressed == true ? 500.0 : 0.0;
		component->setVelocity(v);
	}
};

class MoveLeft : public age::graphics::Command
{
public:
	MoveLeft() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Left);
	}

	void execute(age::core::Entity* x, bool keyPressed) override
	{
		auto component = x->getChild<KinematicComponent>();
		auto v = component->getVelocity();
		v.x() = keyPressed == true ? -500.0 : 0.0;
		component->setVelocity(v);
	}
};

class RotateRight : public age::graphics::Command
{
public:
	RotateRight() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::RShift);
	}

	void execute(age::core::Entity* x, bool keyPressed) override
	{
		auto component = x->getChild<KinematicComponent>();
		auto v = component->getAngularVelocity();
		v = keyPressed == true ? 150.0 : 0.0;
		component->setAngularVelocity(v);
	}
};

class RotateLeft : public age::graphics::Command
{
public:
	RotateLeft() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::LShift);
	}

	void execute(age::core::Entity* x, bool keyPressed) override
	{
		auto component = x->getChild<KinematicComponent>();
		auto v = component->getAngularVelocity();
		v = keyPressed == true ? -150.0 : 0.0;
		component->setAngularVelocity(v);
	}
};

Paddle::Paddle() : Entity()
{
	auto rectangle = std::make_unique<age::graphics::RectangleComponent>();
	rectangle->setSize({25, 100});
	this->addChild(std::move(rectangle));

	auto input = std::make_unique<age::graphics::InputComponent>();
	input->addChild(std::make_unique<MoveUp>());
	input->addChild(std::make_unique<MoveDown>());
	input->addChild(std::make_unique<MoveLeft>());
	input->addChild(std::make_unique<MoveRight>());
	input->addChild(std::make_unique<RotateRight>());
	input->addChild(std::make_unique<RotateLeft>());
	this->addChild(std::move(input));

	this->addChild(std::make_unique<TransformComponent>());
	this->addChild(std::make_unique<KinematicComponent>());
}

Paddle::~Paddle()
{
}

void Paddle::setPosition(const Vector& x)
{
	this->getChild<TransformComponent>()->setPosition(x);
}
