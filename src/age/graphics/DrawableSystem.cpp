#include <age/graphics/DrawableSystem.h>

#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>
#include <age/math/TransformComponent.h>
#include <SFML/Graphics.hpp>

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
	unsigned int pixelsPerMeter{32};
};

DrawableSystem::DrawableSystem()
{
	this->setPixelsPerMeter(this->pimpl->pixelsPerMeter);
}

DrawableSystem::~DrawableSystem()
{
}

void DrawableSystem::setPixelsPerMeter(unsigned int x)
{
	this->pimpl->pixelsPerMeter = x;
	const auto factor = static_cast<float>(x);
	this->pimpl->state.transform.scale(factor, factor);
}

unsigned int DrawableSystem::getPixelsPerMeter() const
{
	return this->pimpl->pixelsPerMeter;
}

void DrawableSystem::render(sf::RenderTarget& target, std::chrono::microseconds /*x*/)
{
	const auto manager = this->getEntityManager();

	manager->each<TransformComponent, std::shared_ptr<sf::Drawable>>(
		[&target, this](Entity, TransformComponent& t, std::shared_ptr<sf::Drawable>& d) {
			auto transform = dynamic_cast<sf::Transformable*>(d.get());

			if(transform != nullptr)
			{
				auto p = t.getPosition();
				transform->setPosition(FromVector(p));
			}

			target.draw(*d, this->pimpl->state);
		});
}
