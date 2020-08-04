#include <azule/core/Configuration.h>
#include <azule/core/Engine.h>
#include <azule/core/EngineState.h>
#include <azule/entity/AnimationComponent.h>
#include <azule/entity/AnimationSystem.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <azule/graphics/InputComponent.h>
#include <azule/graphics/PlayerInputSystem.h>
#include <azule/graphics/RenderSystem.h>
#include <azule/graphics/SpriteComponent.h>
#include <azule/graphics/Window.h>

using namespace azule;
using namespace azule;
using namespace azule;

int main()
{
	Engine engine;
	engine.addChild(std::make_shared<PlayerInputSystem>());
	engine.addChild(std::make_shared<AnimationSystem>());
	auto window = std::make_shared<Window>();
	window->addChild(std::make_unique<RenderSystem>());

	auto manager = std::make_shared<EntityDatabase>();
	engine.addChild(manager);
	engine.addChild(window);
	auto entity = std::make_shared<Entity>();
	manager->addEntity(entity);

	EngineState state;
	state.setState(EngineState::State::StartUp);
	engine.setEngineState(state);

	// Position the entity.
	auto transform = entity->addComponent<TransformComponent>();
	transform->Position = {64, 64};

	// Animation Sprite for the entity.
	auto sprite = entity->addComponent<SpriteComponent>();
	sprite->loadFile(Configuration::Instance().getPathData() / "characters/Filga_1.png");
	sprite->setHFrames(4);
	sprite->setVFrames(4);
	sprite->setFrame(0);

	auto animation = entity->addComponent<AnimationComponent>();

	auto down = animation->create();
	auto& chDown = down->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		auto sprite = entity->getChild<SpriteComponent>();
		if(sprite != nullptr)
		{
			sprite->setFrame(x);
		}
	});

	chDown.addKey({std::chrono::seconds{0}, 0});
	chDown.addKey({std::chrono::seconds{1}, 1});
	chDown.addKey({std::chrono::seconds{2}, 2});
	chDown.addKey({std::chrono::seconds{3}, 3});

	auto up = animation->create();
	auto& chUp = up->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		auto sprite = entity->getChild<SpriteComponent>();
		if(sprite != nullptr)
		{
			sprite->setFrame(x);
		}
	});

	chUp.addKey({std::chrono::seconds{0}, 8});
	chUp.addKey({std::chrono::seconds{1}, 9});
	chUp.addKey({std::chrono::seconds{2}, 10});
	chUp.addKey({std::chrono::seconds{3}, 11});

	auto left = animation->create();
	auto& chLeft = left->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		auto sprite = entity->getChild<SpriteComponent>();
		if(sprite != nullptr)
		{
			sprite->setFrame(x);
		}
	});

	chLeft.addKey({std::chrono::seconds{0}, 12});
	chLeft.addKey({std::chrono::seconds{1}, 13});
	chLeft.addKey({std::chrono::seconds{2}, 14});
	chLeft.addKey({std::chrono::seconds{3}, 15});

	auto right = animation->create();
	auto& chRight = right->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		auto sprite = entity->getChild<SpriteComponent>();
		if(sprite != nullptr)
		{
			sprite->setFrame(x);
		}
	});

	chRight.addKey({std::chrono::seconds{0}, 4});
	chRight.addKey({std::chrono::seconds{1}, 5});
	chRight.addKey({std::chrono::seconds{2}, 6});
	chRight.addKey({std::chrono::seconds{3}, 7});

	animation->setLength(std::chrono::seconds{4});
	animation->setSpeed(10.0);
	animation->play();

	// Controller for the entity.
	auto controller = entity->addComponent<InputComponent>();
	controller->addKeyBinding(sf::Keyboard::Key::Up, [up](Entity& entity, auto isPressed) {
		auto a = entity.getChild<AnimationComponent>();
		if(isPressed == true)
		{
			a->setCurrentAnimation(up);
			a->play();
		}
		else
		{
			a->stop();
			a->reset();
		}
	});

	controller->addKeyBinding(sf::Keyboard::Key::Down, [down](Entity& entity, auto isPressed) {
		auto a = entity.template getChild<AnimationComponent>();
		if(isPressed == true)
		{
			a->setCurrentAnimation(down);
			a->play();
		}
		else
		{
			a->stop();
			a->reset();
		}
	});

	controller->addKeyBinding(sf::Keyboard::Key::Left, [left](auto& entity, auto isPressed) {
		auto a = entity.template getChild<AnimationComponent>();
		if(isPressed == true)
		{
			a->setCurrentAnimation(left);
			a->play();
		}
		else
		{
			a->stop();
			a->reset();
		}
	});

	controller->addKeyBinding(sf::Keyboard::Key::Right, [right](auto& entity, auto isPressed) {
		auto a = entity.template getChild<AnimationComponent>();
		if(isPressed == true)
		{
			a->setCurrentAnimation(right);
			a->play();
		}
		else
		{
			a->stop();
			a->reset();
		}
	});

	while(engine.getEngineState().getState() < EngineState::State::Shutdown)
	{
		engine.frame();
	}

	return 0;
}
