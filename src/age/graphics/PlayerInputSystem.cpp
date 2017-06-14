#include <age/graphics/PlayerInputSystem.h>
#include <age/core/Engine.h>
#include <age/core/Entity.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/Command.h>
#include <age/graphics/KeyEvent.h>

#include <SFML/Window.hpp>

using namespace age::core;
using namespace age::graphics;

PlayerInputSystem::PlayerInputSystem() : VariableSystem()
{
}

PlayerInputSystem::~PlayerInputSystem()
{
}

void PlayerInputSystem::initialize()
{
	this->getParent<Engine>()->addEventHandler([this](auto x){ this->event(x); });
}

void PlayerInputSystem::event(age::core::Event* x)
{
	const auto keyEvent = dynamic_cast<KeyEvent*>(x);
	
	if(keyEvent != nullptr)
	{
		const auto entities = this->getParent<Engine>()->getChildren<Entity>();
	
		for(const auto& entity : entities)
		{
			const auto inputComponent = entity->getChild<InputComponent>();
	
			if(inputComponent != nullptr)
			{
				const auto commands = inputComponent->getChildren<Command>();
				const auto it = std::find_if(std::begin(commands), std::end(commands), [keyEvent](auto c) { return keyEvent->getKey() == c->getMappedKey(); });

				if(it != std::end(commands))
				{
					(*it)->execute(entity, keyEvent->getType() == KeyEvent::Type::Pressed);
				}
			}
		}
	}
}

void PlayerInputSystem::frame(std::chrono::microseconds)
{
	const auto entities = this->getEntities();

	for(const auto& entity : entities)
	{
		const auto inputComponent = entity->getChild<InputComponent>();

		if(inputComponent != nullptr)
		{
			const auto commands = inputComponent->getChildren<Command>();

			for(const auto& command : commands)
			{
				if(sf::Keyboard::isKeyPressed(command->getMappedKey()) == true)
				{
					command->execute(entity, true);
				}
			}
		}
	}
}
