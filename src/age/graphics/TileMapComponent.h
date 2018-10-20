#pragma once

#include <age/terrain/TileMap.h>
#include <SFML/Graphics/Drawable.hpp>
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
			age::terrain::TileMap tileMap;
			sf::Texture texture;
		};
	}
}
