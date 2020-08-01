#pragma once

#include <azule/entity/Component.h>
#include <azule/export.hxx>
#include <azule/terrain/TileMap.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace azule
{
	class AZULE_EXPORT TileMapComponent : public azule::Component, public sf::Drawable
	{
	public:
		TileMapComponent();
		~TileMapComponent();

		void loadTileMap(const azule::TileMap& x);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		std::vector<std::pair<sf::Texture, sf::VertexArray>> layers;
	};
}
