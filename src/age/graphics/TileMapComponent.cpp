#include <age/graphics/TileMapComponent.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

using namespace age::graphics;

TileMapComponent::TileMapComponent()
{
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::loadTileMap(const age::terrain::TileMap& x)
{
	for(const auto& layer : x.getLayers())
	{
		const auto filename = x.getTileSet()[0].getSource().getFileName().string();

		if(this->texture.loadFromFile(filename) == true)
		{
			sf::VertexArray& m_vertices = vertices;
			const auto& indices = layer.getIndices();
			m_vertices.resize(indices.size() * 4);
			m_vertices.setPrimitiveType(sf::Quads);

			// Render order right-down
			for(auto i = 0; i < layer.getHeight(); i++)
			{
				for(auto j = 0; j < layer.getWidth(); j++)
				{
					// Two dimensional index into one dimensional array.
					const auto index = j + (i * layer.getWidth());

					// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
					sf::Vector2u tileSize{static_cast<unsigned int>(x.getTileWidth()), static_cast<unsigned int>(x.getTileHeight())};

					const auto quad = &m_vertices[index * 4];

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
		}
	}
}

void TileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &texture;
	target.draw(vertices, states);
}
