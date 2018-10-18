#include <age/graphics/TileMapComponent.h>

#include <boost/algorithm/string.hpp>
#include <charconv>
#include <pugixml.hpp>

using namespace age::graphics;

TileMapComponent::TileMapComponent()
{
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::loadFile(const std::filesystem::path& x)
{
	if(std::filesystem::exists(x) == true)
	{
		pugi::xml_document doc;
		doc.load_file(x.c_str());

		const auto node = doc.child("map");

		if(node.empty() == false)
		{
			this->tileMap.setHeight(node.attribute("height").as_int());
			this->tileMap.setWidth(node.attribute("width").as_int());
			this->tileMap.setTileHeight(node.attribute("tileheight").as_int());
			this->tileMap.setTileWidth(node.attribute("tilewidth").as_int());

			for(const auto& layer : node.children("layer"))
			{
				const auto data = layer.child("data");

				if(data.empty() == false)
				{
					// TileMap::Layer layer;
					// const auto csv = std::string(data.text().as_string());
					// std::vector<std::string> tiles;
					// boost::split(tiles, csv, boost::is_any_of(","), boost::algorithm::token_compress_on);

					// for(auto i = 0; i < this->tileMap.getHeight(); i++)
					//{
					//	std::vector<int> row;
					//	row.reserve(this->tileMap.getWidth());
					//	for(auto j = 0; j < this->tileMap.getWidth(); j++)
					//	{
					//		const auto& indexStr = tiles[i + j * this->tileMap.getHeight()];
					//		int index{};
					//		std::from_chars(indexStr.data(), indexStr.data() + indexStr.size(), index);
					//		row.push_back(index);
					//	}
					//}

					// std::vector<int> row;

					// for(auto i = 0;)

					//	int index{};
					// std::from_chars(tile.data(), tile.data() + tile.size(), index);
					// v.push_back(index);
				}
			}
		}
	}
}

void TileMapComponent::draw(sf::RenderTarget& /*target*/, sf::RenderStates /*states*/) const
{
}
