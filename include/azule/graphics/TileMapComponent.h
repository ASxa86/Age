#pragma once

#include <azule/entity/Component.h>
#include <azule/graphics/export.h>
#include <azule/terrain/TileMap.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace azule
{
	namespace graphics
	{
		class AZULE_GRAPHICS_EXPORT TileMapComponent : public azule::entity::Component, public sf::Drawable
		{
		public:
			TileMapComponent();
			~TileMapComponent();

			void loadTileMap(const azule::terrain::TileMap& x);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			std::vector<std::pair<sf::Texture, sf::VertexArray>> layers;
		};
	}
}
