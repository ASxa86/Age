#pragma once

#include <age/graphics/TileMap.h>
#include <SFML/Graphics/Texture.hpp>

namespace age
{
	namespace graphics
	{
		class TileMapComponent : public sf::Drawable
		{
		public:
			TileMapComponent();
			~TileMapComponent();

			void loadFile(const std::filesystem::path& x);

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		private:
			TileMap tileMap;
			sf::Texture texture;
		};
	}
}
