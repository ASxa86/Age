#include <azule/terrain/TileSource.h>

using namespace azule;

TileSource::TileSource()
{
}

TileSource::~TileSource()
{
}

void TileSource::setFileName(const std::filesystem::path& x)
{
	this->fileName = x;
}

const std::filesystem::path& TileSource::getFileName() const
{
	return this->fileName;
}

void TileSource::setWidth(int x)
{
	this->width = x;
}

int TileSource::getWidth() const
{
	return this->width;
}

void TileSource::setHeight(int x)
{
	this->height = x;
}

int TileSource::getHeight() const
{
	return this->height;
}
