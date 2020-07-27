#include <azule/terrain/TileMapLayer.h>

using namespace azule::terrain;

TileMapLayer::TileMapLayer() : indices{}, name{}, width{0}, height{0}
{
}

TileMapLayer::~TileMapLayer()
{
}

void TileMapLayer::setName(const std::string& x)
{
	this->name = x;
}

std::string TileMapLayer::getName() const
{
	return this->name;
}

void TileMapLayer::setWidth(int x)
{
	this->width = x;
}

int TileMapLayer::getWidth() const
{
	return this->width;
}

void TileMapLayer::setHeight(int x)
{
	this->height = x;
}

int TileMapLayer::getHeight() const
{
	return this->height;
}

void TileMapLayer::setIndices(const std::vector<int>& x)
{
	this->indices = x;
}
const std::vector<int>& TileMapLayer::getIndices() const
{
	return this->indices;
}
