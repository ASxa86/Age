#include <azule/graphics/DatabaseTexture.h>

using namespace azule::graphics;

sf::Texture& DatabaseTexture::getTexture(const std::string& x)
{
	auto& texture = this->textures[x];

	if(texture.getSize().x == 0 && texture.getSize().y == 0)
	{
		texture.loadFromFile(x);
	}

	return texture;
}
