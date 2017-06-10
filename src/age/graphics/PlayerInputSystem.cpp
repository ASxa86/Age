#include <age/graphics/PlayerInputSystem.h>
#include <age/core/Entity.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/Command.h>

#include <SFML/Window.hpp>

using namespace age::core;
using namespace age::graphics;

PlayerInputSystem::PlayerInputSystem() : VariableSystem()
{
}

PlayerInputSystem::~PlayerInputSystem()
{
}

void PlayerInputSystem::event(age::core::Event* /*x*/)
{
	//auto keyEvent = dynamic_cast<KeyEvent*>(x);
	//
	//if(keyEvent != nullptr)
	//{
	//	auto entities = this->getParent<Engine>()->getChildren<Entity>();
	//
	//	for(const auto& entity : entities)
	//	{
	//		auto inputComponent = entity->getChild<InputComponent>();
	//
	//		if(inputComponent != nullptr)
	//		{
	//			// inputComponent->keyEvent(keyEvent);
	//			auto command = inputComponent->getChildren<EventCommand>(keyEvent->key);
	//			it = std::find(std::begin(command), std::end(command), [keyEvent]{ key == command->getMappedKey() });
	//			(it*)->execute(entity);
	//		}
	//	}
	//}
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
					command->execute(entity);
				}
			}
		}
	}
}
