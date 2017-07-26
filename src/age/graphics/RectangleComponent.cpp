#include <age/graphics/RectangleComponent.h>
#include <age/core/PimplImpl.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace age::core;
using namespace age::graphics;

class RectangleComponent::Impl
{
public:
	sf::RectangleShape rectangle;
};

RectangleComponent::RectangleComponent() : DrawableComponent(), pimpl()
{
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::setSize(const std::array<double, 2>& x)
{
	this->pimpl->rectangle.setSize({static_cast<float>(x[0]), static_cast<float>(x[1])});
}

std::array<double, 2> RectangleComponent::getSize() const
{
	auto size = this->pimpl->rectangle.getSize();
	return{size.x, size.y};
}

void RectangleComponent::draw(sf::RenderTarget& x)
{
	this->updateTransform(this->pimpl->rectangle);
	x.draw(this->pimpl->rectangle);
}
