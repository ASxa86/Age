#include <age/graphics/DrawableSystem.h>

#include <age/core/Configuration.h>
#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/graphics/SpriteComponent.h>
#include <SFML/Graphics.hpp>

using namespace age::core;
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

struct DrawableSystem::Impl
{
	sf::RenderStates state;
};

DrawableSystem::DrawableSystem()
{
	const auto factor = static_cast<float>(Configuration::Instance().getPixelsPerMeter());
	this->pimpl->state.transform.scale(factor, factor);
}

DrawableSystem::~DrawableSystem()
{
}

void DrawableSystem::render(sf::RenderTarget& target, std::chrono::microseconds /*x*/)
{
	const auto manager = this->getEntityManager();

	manager->each<SpriteComponent>([&target, this](Entity& e, SpriteComponent& s) {
		auto& sprite = s.getSprite();

		if(e.hasComponent<TransformComponent>() == true)
		{
			const auto& t = e.getComponent<TransformComponent>();
			const auto p = t.getPosition();
			sprite.setPosition(FromVector(p));
		}

		target.draw(sprite);
		// target.draw(sprite, this->pimpl->state);
	});
}
