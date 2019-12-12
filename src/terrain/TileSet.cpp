#include <age/terrain/TileSet.h>

using namespace age::terrain;

TileSet::TileSet() : source{}, name{}, tileCount{0}, columns{0}, tileWidth{0}, tileHeight{0}, spacing{0}
{
}

TileSet::~TileSet()
{
}

void TileSet::setName(const std::string& x)
{
	this->name = x;
}

const std::string& TileSet::getName() const
{
	return this->name;
}

void TileSet::setTileOffset(int x)
{
	this->tileOffset = x;
}

int TileSet::getTileOffset() const
{
	return this->tileOffset;
}

void TileSet::setTileWidth(int x)
{
	this->tileWidth = x;
}

int TileSet::getTileWidth() const
{
	return this->tileWidth;
}

void TileSet::setTileHeight(int x)
{
	this->tileHeight = x;
}

int TileSet::getTileHeight() const
{
	return this->tileHeight;
}

void TileSet::setSpacing(int x)
{
	this->spacing = x;
}

int TileSet::getSpacing() const
{
	return this->spacing;
}

void TileSet::setTileCount(int x)
{
	this->tileCount = x;
}

int TileSet::getTileCount() const
{
	return this->tileCount;
}

void TileSet::setColumns(int x)
{
	this->columns = x;
}

int TileSet::getColumns() const
{
	return this->columns;
}

void TileSet::setSource(const TileSource& x)
{
	this->source = x;
}

const TileSource& TileSet::getSource() const
{
	return this->source;
}
