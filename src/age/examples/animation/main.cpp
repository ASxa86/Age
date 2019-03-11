#include <age/core/Configuration.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/entity/AnimationComponent.h>
#include <age/entity/AnimationSystem.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/graphics/DrawableSystem.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/PlayerInputSystem.h>
#include <age/graphics/SpriteComponent.h>
#include <age/graphics/Window.h>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;

int main()
{
	Engine engine;
	engine.addChild(std::make_unique<PlayerInputSystem>());
	engine.addChild(std::make_unique<AnimationSystem>());
	auto window = engine.addChild<Window>();
	window->addChild(std::make_unique<DrawableSystem>());

	auto manager = engine.addChild<EntityManager>();
	auto entity = manager->create();

	EngineState state;
	state.setState(EngineState::State::Initialize);
	engine.setEngineState(state);

	// Position the entity.
	auto& transform = entity.addComponent<TransformComponent>();
	transform.Position = {64, 64};

	// Animation Sprite for the entity.
	auto& sprite = entity.addComponent<SpriteComponent>();
	sprite.loadFile(Configuration::Instance().getPathData() / "characters/Filga_1.png");
	sprite.setHFrames(4);
	sprite.setVFrames(4);
	sprite.setFrame(0);

	auto& animation = entity.addComponent<AnimationComponent>();

	auto down = animation.create();
	auto& chDown = down->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		if(entity.valid() == true && entity.hasComponent<SpriteComponent>() == true)
		{
			entity.getComponent<SpriteComponent>().setFrame(x);
		}
	});

	chDown.addKey({std::chrono::seconds{0}, 0});
	chDown.addKey({std::chrono::seconds{1}, 1});
	chDown.addKey({std::chrono::seconds{2}, 2});
	chDown.addKey({std::chrono::seconds{3}, 3});

	auto up = animation.create();
	auto& chUp = up->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		if(entity.valid() == true && entity.hasComponent<SpriteComponent>() == true)
		{
			entity.getComponent<SpriteComponent>().setFrame(x);
		}
	});

	chUp.addKey({std::chrono::seconds{0}, 8});
	chUp.addKey({std::chrono::seconds{1}, 9});
	chUp.addKey({std::chrono::seconds{2}, 10});
	chUp.addKey({std::chrono::seconds{3}, 11});

	auto left = animation.create();
	auto& chLeft = left->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		if(entity.valid() == true && entity.hasComponent<SpriteComponent>() == true)
		{
			entity.getComponent<SpriteComponent>().setFrame(x);
		}
	});

	chLeft.addKey({std::chrono::seconds{0}, 12});
	chLeft.addKey({std::chrono::seconds{1}, 13});
	chLeft.addKey({std::chrono::seconds{2}, 14});
	chLeft.addKey({std::chrono::seconds{3}, 15});

	auto right = animation.create();
	auto& chRight = right->addChannel<int>(Channel::Shape::Step, [entity](int x) {
		if(entity.valid() == true && entity.hasComponent<SpriteComponent>() == true)
		{
			entity.getComponent<SpriteComponent>().setFrame(x);
		}
	});

	chRight.addKey({std::chrono::seconds{0}, 4});
	chRight.addKey({std::chrono::seconds{1}, 5});
	chRight.addKey({std::chrono::seconds{2}, 6});
	chRight.addKey({std::chrono::seconds{3}, 7});

	animation.setLength(std::chrono::seconds{4});
	animation.setSpeed(10.0);
	animation.play();

	// Controller for the entity.
	auto& controller = entity.addComponent<InputComponent>();
	controller.addKeyBinding(sf::Keyboard::Key::Up, [up](Entity& entity, auto isPressed) {
		auto& a = entity.getComponent<AnimationComponent>();
		if(isPressed == true)
		{
			a.setCurrentAnimation(up);
			a.play();
		}
		else
		{
			a.stop();
			a.reset();
		}
	});

	controller.addKeyBinding(sf::Keyboard::Key::Down, [down](Entity& entity, auto isPressed) {
		auto& a = entity.template getComponent<AnimationComponent>();
		if(isPressed == true)
		{
			a.setCurrentAnimation(down);
			a.play();
		}
		else
		{
			a.stop();
			a.reset();
		}
	});

	controller.addKeyBinding(sf::Keyboard::Key::Left, [left](auto& entity, auto isPressed) {
		auto& a = entity.template getComponent<AnimationComponent>();
		if(isPressed == true)
		{
			a.setCurrentAnimation(left);
			a.play();
		}
		else
		{
			a.stop();
			a.reset();
		}
	});

	controller.addKeyBinding(sf::Keyboard::Key::Right, [right](auto& entity, auto isPressed) {
		auto& a = entity.template getComponent<AnimationComponent>();
		if(isPressed == true)
		{
			a.setCurrentAnimation(right);
			a.play();
		}
		else
		{
			a.stop();
			a.reset();
		}
	});

	while(engine.getEngineState().getState() < EngineState::State::Exit)
	{
		engine.frame();
	}

	return 0;
}
