#include <age/graphics/CircleComponent.h>
#include <age/core/PimplImpl.h>
#include <age/core/TransformComponent.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

using namespace age::core;
using namespace age::graphics;

class CircleComponent::Impl
{
public:
	sf::CircleShape circle;
};

CircleComponent::CircleComponent() : DrawableComponent(), pimpl()
{
}

CircleComponent::~CircleComponent()
{
}

void CircleComponent::setRadius(double x)
{
	this->pimpl->circle.setRadius(static_cast<float>(x));
}

double CircleComponent::getRadius() const
{
	return this->pimpl->circle.getRadius();
}

void CircleComponent::draw(sf::RenderTarget& x)
{
	auto entity = this->getParent();
	auto transform = entity->getChild<TransformComponent>();
	auto pos = transform->getPosition();
	this->pimpl->circle.setPosition(static_cast<float>(pos[0]), static_cast<float>(pos[1]));
	this->pimpl->circle.setRotation(static_cast<float>(transform->getRotation()));
	x.draw(this->pimpl->circle);
}
