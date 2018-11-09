#pragma once

#include <age/graphics/Export.h>
#include <age/terrain/TileMap.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace age
{
	namespace graphics
	{
		class AGE_GRAPHICS_EXPORT TileMapComponent : public sf::Drawable
		{
		public:
			struct Layer
			{
				std::vector<sf::VertexArray> arrays{};
				sf::Texture Texture{};
			};

			TileMapComponent();
			~TileMapComponent();

			void loadTileMap(const age::terrain::TileMap& x);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			// std::vector<Layer> layers;
			sf::VertexArray vertices;
			sf::Texture texture;
		};
	}
}
