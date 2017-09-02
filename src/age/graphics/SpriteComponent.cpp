#include <age/graphics/SpriteComponent.h>
#include <age/core/PimplImpl.h>

#include <SFML/Graphics.hpp>

using namespace age::graphics;

class SpriteComponent::Impl
{
public:
	sf::Sprite sprite;
};

SpriteComponent::SpriteComponent() : DrawableComponent(), pimpl()
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::setSprite(const sf::Sprite& x)
{
	this->pimpl->sprite = x;
}

sf::Sprite SpriteComponent::getSprite() const
{
	return this->pimpl->sprite;
}

void SpriteComponent::draw(sf::RenderTarget& x, unsigned int pixelsPerMeter)
{
	this->updateTransform(this->pimpl->sprite, pixelsPerMeter);
	x.draw(this->pimpl->sprite);
}
