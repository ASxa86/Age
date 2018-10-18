#include <age/graphics/TileMap.h>

using namespace age::graphics;

TileMap::TileMap() : layers{}, width{}, height{}, tileWidth{}, tileHeight{}
{
}

TileMap::~TileMap()
{
}

void TileMap::addLayer(const Layer& x)
{
	this->layers.push_back(x);
}

const std::vector<TileMap::Layer>& TileMap::getLayers() const
{
	return this->layers;
}

void TileMap::setWidth(int x)
{
	this->width = x;
}

int TileMap::getWidth() const
{
	return this->width;
}

void TileMap::setHeight(int x)
{
	this->height = x;
}

int TileMap::getHeight() const
{
	return this->height;
}

void TileMap::setTileHeight(int x)
{
	this->tileHeight = x;
}

int TileMap::getTileHeight() const
{
	return this->tileHeight;
}

void TileMap::setTileWidth(int x)
{
	this->tileWidth = x;
}

int TileMap::getTileWidth() const
{
	return this->tileHeight;
}
