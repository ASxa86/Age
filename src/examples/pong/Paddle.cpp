#include <examples/pong/Paddle.h>
#include <age/graphics/RectangleComponent.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/Command.h>
#include <age/math/TransformComponent.h>
#include <age/physics/KinematicComponent.h>
#include <boost/qvm/vec_access.hpp>

using namespace boost::qvm;
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
		Y(v) = keyPressed == true ? -500.0 : 0.0;
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
		Y(v) = keyPressed == true ? 500.0 : 0.0;
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
		X(v) = keyPressed == true ? 500.0 : 0.0;
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
		X(v) = keyPressed == true ? -500.0 : 0.0;
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
		v = keyPressed == true ? 25.0 : 0.0;
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
		v = keyPressed == true ? -25.0 : 0.0;
		component->setAngularVelocity(v);
	}
};

Paddle::Paddle() : Entity()
{
	auto rectangle = std::make_shared<age::graphics::RectangleComponent>();
	rectangle->setSize({25, 100});
	this->addChild(rectangle);

	auto input = std::make_shared<age::graphics::InputComponent>();
	input->addChild(std::make_shared<MoveUp>());
	input->addChild(std::make_shared<MoveDown>());
	input->addChild(std::make_shared<MoveLeft>());
	input->addChild(std::make_shared<MoveRight>());
	input->addChild(std::make_shared<RotateRight>());
	input->addChild(std::make_shared<RotateLeft>());
	this->addChild(input);

	this->addChild(std::make_shared<TransformComponent>());
	this->addChild(std::make_shared<KinematicComponent>());
}

Paddle::~Paddle()
{
}

void Paddle::setPosition(const vec<double, 2>& x)
{
	this->getChild<TransformComponent>()->setPosition(x);
	this->getChild<KinematicComponent>()->setPosition(x);
}
