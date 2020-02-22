#include <age/core/Reflection.h>
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
		this->file = x;
		this->sprite.setTexture(this->texture, true);
		this->updateTextureRect();
	}
}

const std::filesystem::path& SpriteComponent::getFile() const
{
	return this->file;
}

void SpriteComponent::setFrame(unsigned int x)
{
	this->frame = x;
	this->updateTextureRect();
}

unsigned int SpriteComponent::getFrame() const
{
	return this->frame;
}

void SpriteComponent::setVFrames(unsigned int x)
{
	this->vFrames = x;
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
	const auto vFrames = std::min(this->vFrames, this->getFrameCount());
	const auto frame = std::min(this->frame, this->getFrameCount());
	const auto frameSize = sf::Vector2i{static_cast<int>(textureSize.x / this->hFrames), static_cast<int>(textureSize.y / vFrames)};
	const auto px = static_cast<int>(frameSize.x * (frame % this->hFrames));
	const auto py = static_cast<int>(frameSize.y * (frame / vFrames));

	const auto framePos = sf::Vector2i{px, py};
	this->sprite.setTextureRect(sf::IntRect(framePos, frameSize));
	this->sprite.setOrigin(frameSize.x / 2.0f, frameSize.y / 2.0f);
}
