#include <age/graphics/RectangleComponent.h>
#include <age/core/Entity.h>
#include <age/core/PimplImpl.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <age/core/TransformComponent.h>

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
	auto entity = this->getParent();
	auto transform = entity->getChild<TransformComponent>();
	auto pos = transform->getPosition();
	this->pimpl->rectangle.setPosition(static_cast<float>(pos[0]), static_cast<float>(pos[1]));
	this->pimpl->rectangle.setRotation(static_cast<float>(transform->getRotation()));
	x.draw(this->pimpl->rectangle);
}
