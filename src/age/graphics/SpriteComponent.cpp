#include <age/graphics/SpriteComponent.h>
#include <age/core/PimplImpl.h>

using namespace age::graphics;

class SpriteComponent::Impl
{
public:
	sf::Sprite sprite;
};

SpriteComponent::SpriteComponent() : Object(), pimpl()
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
