#include <age/plugins/tmx/ParserTMX.h>

#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/graphics/TileMapComponent.h>
#include <age/terrain/TileMap.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <charconv>
#include <pugixml.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;
using namespace age::tmx;

ParserTMX::ParserTMX()
{
}

ParserTMX::~ParserTMX()
{
}

bool ParserTMX::readFile(const std::filesystem::path& x, Object* obj)
{
	auto manager = dynamic_cast<EntityDatabase*>(obj);
	if(std::filesystem::exists(x) == true && x.extension() == ".tmx" && manager != nullptr)
	{
		pugi::xml_document doc;
		const auto result = doc.load_file(x.c_str());

		if(result.status == pugi::xml_parse_status::status_ok)
		{
			for(const auto& map : doc.children("map"))
			{
				auto entity = manager->addEntity();
				age::terrain::TileMap tileMap;
				tileMap.setWidth(map.attribute("width").as_int());
				tileMap.setHeight(map.attribute("height").as_int());
				tileMap.setTileWidth(map.attribute("tilewidth").as_int());
				tileMap.setTileHeight(map.attribute("tileheight").as_int());

				for(const auto& tileset : map.children("tileset"))
				{
					age::terrain::TileSet tileSet;
					tileSet.setTileOffset(tileset.attribute("firstgid").as_int());
					tileSet.setName(tileset.attribute("name").as_string());
					tileSet.setTileWidth(tileset.attribute("tilewidth").as_int());
					tileSet.setTileHeight(tileset.attribute("tileheight").as_int());
					tileSet.setSpacing(tileset.attribute("spacing").as_int());
					tileSet.setTileCount(tileset.attribute("tilecount").as_int());
					tileSet.setColumns(tileset.attribute("columns").as_int());

					const auto image = tileset.child("image");

					if(image.empty() == false)
					{
						age::terrain::TileSource source;
						source.setFileName(x.parent_path() / image.attribute("source").as_string());
						source.setWidth(image.attribute("width").as_int());
						source.setHeight(image.attribute("height").as_int());
						tileSet.setSource(source);
					}

					tileMap.addTileSet(tileSet);
				}

				for(const auto& layer : map.children("layer"))
				{
					age::terrain::TileMapLayer mapLayer;
					mapLayer.setName(layer.attribute("name").as_string());
					mapLayer.setWidth(layer.attribute("width").as_int());
					mapLayer.setHeight(layer.attribute("height").as_int());

					const auto data = layer.child("data");

					if(data.empty() == false)
					{
						const auto encoding = std::string(data.attribute("encoding").as_string());

						if(encoding == "csv")
						{
							const auto csv = std::string(data.text().as_string());
							std::vector<std::string> splitCSV;
							boost::split(splitCSV, csv, boost::is_any_of(",\n"), boost::algorithm::token_compress_on);
							std::vector<int> indices;
							indices.reserve(mapLayer.getWidth() * mapLayer.getHeight());

							for(const auto& token : splitCSV)
							{
								if(token.empty() == false)
								{
									indices.push_back(boost::lexical_cast<int>(token));
								}
							}

							mapLayer.setIndices(indices);
						}
					}

					tileMap.addLayer(mapLayer);
				}

				auto tileMapComponent = entity->addComponent<TileMapComponent>();
				tileMapComponent->loadTileMap(tileMap);
			}

			return true;
		}
	}

	return false;
}
