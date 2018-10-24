#include <age/graphics/TileMapComponent.h>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace age::graphics;

TileMapComponent::TileMapComponent()
{
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::loadTileMap(const age::terrain::TileMap& x)
{
	for(const auto& tileset : x.getTileSet())
	{
		Layer layer;

		layer.Texture.loadFromFile(tileset.getSource().getFileName().string());

		this->layers.push_back(layer);
	}

	for(const auto& layer : x.getLayers())
	{
		Layer mapLayer;
		mapLayer.Texture.loadFromFile(x.getTileSet()[0].getSource().getFileName().string());
		sf::VertexArray m_vertices;
		const auto& indices = layer.getIndices();
		m_vertices.resize(indices.size() * 4);

		// Render order right-down
		for(auto i = 0; i < layer.getHeight(); i++)
		{
			for(auto j = 0; j < layer.getWidth(); j++)
			{
				// Two dimensional index into one dimensional array.
				const auto index = j + i * layer.getWidth();

				// Use index to find tileset reference?
				// If index is greater than max tiles, load next tileset
				// and build another layer.
				// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
				const auto tile = indices[index];

				sf::Vector2u tileSize{static_cast<unsigned int>(x.getTileWidth()), static_cast<unsigned int>(x.getTileHeight())};

				int tu = tile % (mapLayer.Texture.getSize().x / tileSize.x);
				int tv = tile / (mapLayer.Texture.getSize().x / tileSize.x);

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[index * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>(j * tileSize.y));
				quad[1].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>(j * tileSize.y));
				quad[2].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>((j + 1) * tileSize.y));
				quad[3].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>((j + 1) * tileSize.y));

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>(tv * tileSize.y));
				quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y));
				quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
				quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
			}
		}

		mapLayer.arrays.push_back(m_vertices);
		this->layers.push_back(mapLayer);
	}
}

void TileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& layer : this->layers)
	{
		for(const auto& vertices : layer.arrays)
		{
			states.texture = &layer.Texture;
			target.draw(vertices, states);
		}
	}
}
