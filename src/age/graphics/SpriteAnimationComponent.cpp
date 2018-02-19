#include <age/graphics/SpriteAnimationComponent.h>

using namespace age::graphics;

SpriteAnimationComponent::SpriteAnimationComponent()
{
}

SpriteAnimationComponent::~SpriteAnimationComponent()
{
}

SpriteAnimation& SpriteAnimationComponent::getCurrentAnimation()
{
	return this->animations[0];
}
