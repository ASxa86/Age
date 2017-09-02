#include <age/graphics/CircleComponent.h>
#include <age/core/PimplImpl.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

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

void CircleComponent::draw(sf::RenderTarget& x, unsigned int pixelsPerMeter)
{
	this->updateTransform(this->pimpl->circle, pixelsPerMeter);
	x.draw(this->pimpl->circle);
}
