#include <examples/pong/Paddle.h>
#include <age/graphics/RectangleComponent.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/Command.h>
#include <age/core/TransformComponent.h>

using namespace age::core;
using namespace age::graphics;
using namespace age::pong;

class MoveUpCommand : public age::graphics::Command
{
public:
	MoveUpCommand() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Up);
	}

	void execute(age::core::Entity* x) override
	{
		auto component = x->getChild<age::core::TransformComponent>();
		auto pos = component->getPosition();
		pos[1]--;
		component->setPosition(pos);
	}
};

class MoveDownCommand : public age::graphics::Command
{
public:
	MoveDownCommand() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Down);
	}

	void execute(age::core::Entity* x) override
	{
		auto component = x->getChild<age::core::TransformComponent>();
		auto pos = component->getPosition();
		pos[1]++;
		component->setPosition(pos);
	}
};

class RotateRight : public age::graphics::Command
{
public:
	RotateRight() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Right);
	}

	void execute(age::core::Entity* x) override
	{
		auto component = x->getChild<age::core::TransformComponent>();
		auto rot = component->getRotation();
		rot++;
		component->setRotation(rot);
	}
};

class RotateLeft : public age::graphics::Command
{
public:
	RotateLeft() : Command()
	{
		this->setMappedKey(sf::Keyboard::Key::Left);
	}

	void execute(age::core::Entity* x) override
	{
		auto component = x->getChild<age::core::TransformComponent>();
		auto rot = component->getRotation();
		rot--;
		component->setRotation(rot);
	}
};

Paddle::Paddle() : Entity()
{
	auto rectangle = std::make_unique<age::graphics::RectangleComponent>();
	rectangle->setSize({100, 100});
	this->addChild(std::move(rectangle));

	auto input = std::make_unique<age::graphics::InputComponent>();
	input->addChild(std::make_unique<MoveUpCommand>());
	input->addChild(std::make_unique<MoveDownCommand>());
	input->addChild(std::make_unique<RotateRight>());
	input->addChild(std::make_unique<RotateLeft>());
	this->addChild(std::move(input));

	auto transform = std::make_unique<age::core::TransformComponent>();
	this->addChild(std::move(transform));
}

Paddle::~Paddle()
{
}
