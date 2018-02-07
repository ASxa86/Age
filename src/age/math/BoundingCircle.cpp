#include <age/math/BoundingCircle.h>

using namespace age::math;

BoundingCircle::BoundingCircle() : position{}, radius{}
{
}

BoundingCircle::BoundingCircle(const Vector& p, double r) : position{p}, radius{r}
{
}

BoundingCircle::~BoundingCircle()
{
}

void BoundingCircle::setPosition(const Vector& x)
{
	this->position = x;
}

Vector BoundingCircle::getPosition() const
{
	return this->position;
}

void BoundingCircle::setRadius(double x)
{
	this->radius = x;
}

double BoundingCircle::getRadius() const
{
	return this->radius;
}
