#include <azule/graphics/TileMapSystem.h>

#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/graphics/TileMapComponent.h>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace azule;
using namespace azule;

TileMapSystem::TileMapSystem()
{
}

TileMapSystem::~TileMapSystem()
{
}

void TileMapSystem::render(sf::RenderTarget& target, std::chrono::microseconds)
{
	const auto manager = this->getEntityDatabase();

	for(auto entity : manager->getChildren<Entity>())
	{
		auto tileMap = entity->getChild<TileMapComponent>();

		if(tileMap != nullptr)
		{
			target.draw(*tileMap);
		}
	}
}
