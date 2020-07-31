#include <azule/core/Engine.h>
#include <azule/core/EventQueue.h>
#include <azule/utilities/Signal.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/graphics/InputComponent.h>
#include <azule/graphics/KeyEvent.h>
#include <azule/graphics/PlayerInputSystem.h>
#include <SFML/Window.hpp>

using namespace azule;
using namespace azule;
using namespace azule;

PlayerInputSystem::PlayerInputSystem() : System()
{
	this->addVariableFunction([this](auto x) { this->frame(x); });
}

PlayerInputSystem::~PlayerInputSystem()
{
}

void PlayerInputSystem::onStartup()
{
	this->track(EventQueue::Instance().addEventHandler([this](auto x) { this->event(x); }));
}

void PlayerInputSystem::event(azule::Event* x)
{
	const auto keyEvent = dynamic_cast<KeyEvent*>(x);

	if(keyEvent != nullptr)
	{
		const auto manager = this->getEntityDatabase();

		for(auto entity : manager->getChildren<Entity>())
		{
			auto i = entity->getChild<InputComponent>();

			if(i != nullptr)
			{
				const auto& keyBindings = i->getKeyBindings();
				const auto foundIt =
					std::find_if(std::begin(keyBindings), std::end(keyBindings), [keyEvent](auto c) { return keyEvent->getKey() == c.first; });

				if(foundIt != std::end(keyBindings))
				{
					foundIt->second(*entity, keyEvent->getType() == KeyEvent::Type::Pressed);
				}
			}
		}
	}
}

void PlayerInputSystem::frame(std::chrono::microseconds)
{
	const auto manager = this->getEntityDatabase();

	for(auto entity : manager->getChildren<Entity>())
	{
		auto i = entity->getChild<InputComponent>();

		if(i != nullptr)
		{
			for(const auto& keyBinding : i->getKeyBindings())
			{
				if(sf::Keyboard::isKeyPressed(keyBinding.first) == true)
				{
					keyBinding.second(*entity, true);
				}
			}
		}
	}
}
