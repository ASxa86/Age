#pragma once

#include <age/core/Object.h>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

namespace age
{
	namespace graphics
	{
		class DatabaseTexture : public age::core::Object
		{
		public:
			sf::Texture& getTexture(const std::string& x);

		private:
			std::unordered_map<std::string, sf::Texture> textures;
		};
	}
}
