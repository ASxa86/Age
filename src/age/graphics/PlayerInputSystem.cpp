#include <age/core/Engine.h>
#include <age/core/EventQueue.h>
#include <age/entity/EntityManager.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/KeyEvent.h>
#include <age/graphics/PlayerInputSystem.h>
#include <SFML/Window.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;

PlayerInputSystem::PlayerInputSystem() : System()
{
	this->addVariableFunction([this](auto x) {this->frame(x); });
}

PlayerInputSystem::~PlayerInputSystem()
{
}

void PlayerInputSystem::initialize()
{
	EventQueue::Instance().addEventHandler([this](auto x) { this->event(x); }, this);
}

void PlayerInputSystem::event(age::core::Event* x)
{
	const auto keyEvent = dynamic_cast<KeyEvent*>(x);

	if(keyEvent != nullptr)
	{
		const auto manager = this->getEntityManager();

		manager->each<InputComponent>([&keyEvent](Entity e, InputComponent& i) {
			const auto& keyBindings = i.getKeyBindings();
			const auto foundIt = std::find_if(std::begin(keyBindings), std::end(keyBindings), [keyEvent](auto c) { return keyEvent->getKey() == c.first; });

			if(foundIt != std::end(keyBindings))
			{
				foundIt->second(e, keyEvent->getType() == KeyEvent::Type::Pressed);
			}
		});
	}
}

void PlayerInputSystem::frame(std::chrono::microseconds)
{
	const auto manager = this->getEntityManager();

	manager->each<InputComponent>([](Entity e, InputComponent& i) {
		for(const auto& keyBinding : i.getKeyBindings())
		{
			if(sf::Keyboard::isKeyPressed(keyBinding.first) == true)
			{
				keyBinding.second(e, true);
			}
		}
	});
}
