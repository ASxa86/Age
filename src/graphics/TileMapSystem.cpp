#include <age/graphics/TileMapSystem.h>

#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/graphics/TileMapComponent.h>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace age::entity;
using namespace age::graphics;

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
