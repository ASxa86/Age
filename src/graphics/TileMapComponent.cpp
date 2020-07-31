#include <azule/graphics/TileMapComponent.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace azule;

TileMapComponent::TileMapComponent()
{
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::loadTileMap(const azule::TileMap& x)
{
	for(const auto& layer : x.getLayers())
	{
		sf::Texture texture;
		sf::VertexArray vertices;
		const auto filename = x.getTileSet()[0].getSource().getFileName().string();

		if(texture.loadFromFile(filename) == true)
		{
			const auto& indices = layer.getIndices();
			vertices.resize(indices.size() * 4);
			vertices.setPrimitiveType(sf::Quads);

			// Render order right-down
			for(auto i = 0; i < layer.getHeight(); i++)
			{
				for(auto j = 0; j < layer.getWidth(); j++)
				{
					// Two dimensional index into one dimensional array.
					const auto index = j + (i * layer.getWidth());

					// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
					sf::Vector2u tileSize{static_cast<unsigned int>(x.getTileWidth()), static_cast<unsigned int>(x.getTileHeight())};

					const auto quad = &vertices[index * 4];

					// Define the size and shape on screen to draw the texture at.
					quad[0].position = sf::Vector2f(static_cast<float>(j * tileSize.x), static_cast<float>(i * tileSize.y));
					quad[1].position = sf::Vector2f(static_cast<float>((j + 1) * tileSize.x), static_cast<float>(i * tileSize.y));
					quad[2].position = sf::Vector2f(static_cast<float>((j + 1) * tileSize.x), static_cast<float>((i + 1) * tileSize.y));
					quad[3].position = sf::Vector2f(static_cast<float>(j * tileSize.x), static_cast<float>((i + 1) * tileSize.y));

					// Define the location of the tile within the texture.
					// We must account for the spacing between tiles that may appear within the tileset texture.
					const auto& tileset = x.getTileSet()[0];
					const auto tile = indices[index] - tileset.getTileOffset();
					const auto tu = tile % tileset.getColumns();
					const auto tv = tile / tileset.getColumns();
					const auto su = tu * tileset.getSpacing();
					const auto sv = tv * tileset.getSpacing();
					quad[0].texCoords = sf::Vector2f(static_cast<float>(su + tu * tileSize.x), static_cast<float>(sv + tv * tileSize.y));
					quad[1].texCoords = sf::Vector2f(static_cast<float>(su + (tu + 1) * tileSize.x), static_cast<float>(sv + tv * tileSize.y));
					quad[2].texCoords = sf::Vector2f(static_cast<float>(su + (tu + 1) * tileSize.x), static_cast<float>(sv + (tv + 1) * tileSize.y));
					quad[3].texCoords = sf::Vector2f(static_cast<float>(su + tu * tileSize.x), static_cast<float>(sv + (tv + 1) * tileSize.y));
				}
			}

			this->layers.push_back({texture, vertices});
		}
	}
}

void TileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& layer : this->layers)
	{
		states.texture = &layer.first;
		target.draw(layer.second, states);
	}
}
