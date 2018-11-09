#include <age/graphics/TileMapSystem.h>

#include <age/entity/EntityManager.h>
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
	const auto manager = this->getEntityManager();

	manager->each<TileMapComponent>([&target](auto&, TileMapComponent& tileMap) {
		// Use some kind of camera to determine bounds and apply a culling mask to the tile map
		target.draw(tileMap);
	});
}
