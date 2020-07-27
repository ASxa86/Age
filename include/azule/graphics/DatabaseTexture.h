#pragma once

#include <azule/core/Object.h>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

namespace azule
{
	namespace graphics
	{
		class DatabaseTexture : public azule::core::Object
		{
		public:
			sf::Texture& getTexture(const std::string& x);

		private:
			std::unordered_map<std::string, sf::Texture> textures;
		};
	}
}
