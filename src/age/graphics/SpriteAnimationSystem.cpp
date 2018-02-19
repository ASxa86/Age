#include <age/entity/EntityManager.h>
#include <age/graphics/SpriteAnimation.h>
#include <age/graphics/SpriteAnimationComponent.h>
#include <age/graphics/SpriteAnimationSystem.h>
#include <age/math/TransformComponent.h>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace age::entity;
using namespace age::graphics;
using namespace age::math;

namespace
{
	sf::Vector2f FromVector(const age::math::Vector& x)
	{
		return {static_cast<float>(x.getX()), static_cast<float>(x.getY())};
	}
}

SpriteAnimationSystem::SpriteAnimationSystem()
{
}

SpriteAnimationSystem::~SpriteAnimationSystem()
{
}

void SpriteAnimationSystem::render(sf::RenderTarget& target, sf::RenderStates& state, std::chrono::microseconds x)
{
	const auto manager = this->getEntityManager();

	manager->each<TransformComponent, SpriteAnimationComponent>([&target, &state, x](Entity, TransformComponent& t, SpriteAnimationComponent& a) {

		auto& animation = a.getCurrentAnimation();
		const auto elapsed = animation.getElapsedTime() + x;
		animation.setElapsedTime(elapsed);

		if(elapsed >= animation.getCurrentTime())
		{
			animation.setElapsedTime(elapsed - animation.getCurrentTime());
			animation.setNextFrame();
		}

		auto& sprite = animation.getCurrentSprite();
		sprite.setPosition(FromVector(t.getPosition()));
		target.draw(sprite, state);
	});
}
