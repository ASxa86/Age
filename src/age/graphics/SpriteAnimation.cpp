#include <age/graphics/SpriteAnimation.h>
#include <SFML/Graphics/Sprite.hpp>

using namespace age::graphics;

SpriteAnimation::SpriteAnimation() : elapsedTime{}, currentIndex{}
{
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::addSprite(std::chrono::microseconds t, const sf::Sprite& x)
{
	this->sprites.push_back(std::make_pair(t, x));
}

sf::Sprite& SpriteAnimation::getCurrentSprite()
{
	return this->sprites[this->currentIndex].second;
}

std::chrono::microseconds SpriteAnimation::getCurrentTime() const
{
	return this->sprites[this->currentIndex].first;
}

void SpriteAnimation::setElapsedTime(std::chrono::microseconds x)
{
	this->elapsedTime = x;
}

std::chrono::microseconds SpriteAnimation::getElapsedTime() const
{
	return this->elapsedTime;
}

void SpriteAnimation::setNextFrame()
{
	this->currentIndex++;

	if(this->currentIndex >= this->sprites.size())
	{
		this->currentIndex = 0;
	}
}
