#include <azule/graphics/SpriteComponent.h>

#include <azule/core/Engine.h>
#include <azule/core/Reflection.h>
#include <azule/graphics/DatabaseTexture.h>

using namespace azule::graphics;

SpriteComponent::SpriteComponent() : frame{0}, vFrames{1}, hFrames{1}
{
	this->UseRotation = true;
	this->UsePosition = true;
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::loadFile(const std::filesystem::path& x)
{
	this->file = x;

	auto engine = this->getParent<azule::core::Engine>(FindOption::Recursive);

	if(engine != nullptr)
	{
		auto dbTexture = engine->getChild<DatabaseTexture>();

		if(dbTexture != nullptr)
		{
			this->sprite.setTexture(dbTexture->getTexture(x.string()), true);
			this->updateTextureRect();
		}
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

const sf::Drawable* SpriteComponent::getDrawable()
{
	return &this->sprite;
}

void SpriteComponent::onStartup()
{
	this->loadFile(this->file);
}

void SpriteComponent::updateTextureRect()
{
	const auto textureWidth = this->sprite.getTextureRect().width;
	const auto textureHeight = this->sprite.getTextureRect().height;
	const auto vFrames = std::min(this->vFrames, this->getFrameCount());
	const auto frame = std::min(this->frame, this->getFrameCount());
	const auto frameSize = sf::Vector2i{static_cast<int>(textureWidth / this->hFrames), static_cast<int>(textureHeight / vFrames)};
	const auto px = static_cast<int>(frameSize.x * (frame % this->hFrames));
	const auto py = static_cast<int>(frameSize.y * (frame / vFrames));

	const auto framePos = sf::Vector2i{px, py};
	this->sprite.setTextureRect(sf::IntRect(framePos, frameSize));
	this->sprite.setOrigin(frameSize.x / 2.0f, frameSize.y / 2.0f);
	this->sprite.setRotation(static_cast<float>(this->Rotation));
}
