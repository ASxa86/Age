#include <age/graphics/PlayerInputSystem.h>
#include <age/core/Engine.h>
#include <age/graphics/InputComponent.h>
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
		//const auto entities = this->getParent<Engine>()->getChildren<Entity>();
	
		//for(const auto& entity : entities)
		//{
		//	const auto inputComponent = entity->getChild<InputComponent>();
	
		//	if(inputComponent != nullptr)
		//	{
		//		const auto commands = inputComponent->getChildren<Command>();
		//		const auto it = std::find_if(std::begin(commands), std::end(commands), [keyEvent](auto c) { return keyEvent->getKey() == c->getMappedKey(); });

		//		if(it != std::end(commands))
		//		{
		//			(*it)->execute(entity.get(), keyEvent->getType() == KeyEvent::Type::Pressed);
		//		}
		//	}
		//}
	}
}

void PlayerInputSystem::frame(const std::vector<age::entity::Entity>& entities, std::chrono::microseconds)
{
	for(auto entity : entities)
	{
		if(entity.valid() == true && entity.hasComponent<InputComponent>() == true)
		{
			const auto inputComponent = entity.getComponent<InputComponent>();

			for(const auto& keyBinding : inputComponent.getKeyBindings())
			{
				if(sf::Keyboard::isKeyPressed(keyBinding.first) == true)
				{
					keyBinding.second(entity, true);
				}
			}
		}
	}
}
