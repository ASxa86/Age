#pragma once

#include <age/entity/Component.h>
#include <age/graphics/Export.h>
#include <age/terrain/TileMap.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace age
{
	namespace graphics
	{
		class AGE_GRAPHICS_EXPORT TileMapComponent : public age::entity::Component, public sf::Drawable
		{
		public:
			TileMapComponent();
			~TileMapComponent();

			void loadTileMap(const age::terrain::TileMap& x);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			std::vector<std::pair<sf::Texture, sf::VertexArray>> layers;
		};
	}
}
