#include <age/math/BoundingBox.h>

using namespace age::math;

BoundingBox::BoundingBox() : position{}, size{}
{
}

BoundingBox::BoundingBox(const Vector& p, const Vector& s) : position{p}, size{s}
{
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::setPosition(const Vector& x)
{
	this->position = x;
}

Vector BoundingBox::getPosition() const
{
	return this->position;
}

void BoundingBox::setSize(const Vector& x)
{
	this->size = x;
}

Vector BoundingBox::getSize() const
{
	return this->size;
}

double BoundingBox::getLeft() const
{
	return this->position.getX() - (this->size.getX() * 0.5);
}

double BoundingBox::getRight() const
{
	return this->position.getX() + (this->size.getX() * 0.5);
}

double BoundingBox::getTop() const
{
	return this->position.getY() - (this->size.getY() * 0.5);
}

double BoundingBox::getBottom() const
{
	return this->position.getY() + (this->size.getY() * 0.5);
}
