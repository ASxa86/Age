#include <age/graphics/SpriteComponent.h>

using namespace age::graphics;

SpriteComponent::SpriteComponent() : frame{0}, vFrames{1}, hFrames{1}
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::loadFile(const std::filesystem::path& x)
{
	if(this->texture.loadFromFile(x.string()) == true)
	{
		this->sprite.setTexture(this->texture, true);
		this->updateTextureRect();
	}
}

void SpriteComponent::setFrame(unsigned int x)
{
	this->frame = std::min(x, this->hFrames * this->vFrames);
	this->updateTextureRect();
}

unsigned int SpriteComponent::getFrame() const
{
	return this->frame;
}

void SpriteComponent::setVFrames(unsigned int x)
{
	this->vFrames = std::min(x, this->getFrameCount());
	this->updateTextureRect();
}

unsigned int SpriteComponent::getVFrames() const
{
	return this->vFrames;
}

void SpriteComponent::setHFrames(unsigned int x)
{
	this->hFrames = x;
	this->updateTextureRect();
}

unsigned int SpriteComponent::getHFrames() const
{
	return this->hFrames;
}

unsigned int SpriteComponent::getFrameCount() const
{
	return this->hFrames * this->vFrames;
}

sf::Sprite& SpriteComponent::getSprite()
{
	return this->sprite;
}

void SpriteComponent::updateTextureRect()
{
	const auto textureSize = this->texture.getSize();
	const auto frameSize = sf::Vector2i{static_cast<int>(textureSize.x / this->hFrames), static_cast<int>(textureSize.y / this->vFrames)};
	const auto px = static_cast<int>(frameSize.x * (this->frame % this->hFrames));
	const auto py = static_cast<int>(frameSize.y * (this->frame / this->vFrames));

	const auto framePos = sf::Vector2i{px, py};
	this->sprite.setTextureRect(sf::IntRect(framePos, frameSize));
}
