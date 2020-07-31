#pragma once

#include <azule/core/Object.h>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

namespace azule
{
	class DatabaseTexture : public azule::Object
	{
	public:
		sf::Texture& getTexture(const std::string& x);

	private:
		std::unordered_map<std::string, sf::Texture> textures;
	};
}
