#include <age/math/Vector.h>
#include <array>
#include <cmath>

using namespace age::math;

Vector::Vector() : v{}
{
}

Vector::Vector(double x, double y) : v{{x, y}}
{
}

Vector::~Vector()
{
}

void Vector::setX(double x)
{
	this->v[0] = x;
}

double Vector::getX() const
{
	return this->v[0];
}

void Vector::setY(double x)
{
	this->v[1] = x;
}

double Vector::getY() const
{
	return this->v[1];
}

Vector Vector::operator+(const Vector& x) const
{
	return Vector(this->v[0] + x.v[0], this->v[1] + x.v[1]);
}

Vector& Vector::operator+=(const Vector& x)
{
	this->v[0] += x.v[0];
	this->v[1] += x.v[1];
	return *this;
}

Vector Vector::operator-(const Vector& x) const
{
	return Vector(this->v[0] - x.v[0], this->v[1] - x.v[1]);
}

Vector& Vector::operator-=(const Vector& x)
{
	this->v[0] -= x.v[0];
	this->v[1] -= x.v[1];
	return *this;
}

double Vector::operator*(const Vector& x) const
{
	return this->v[0] * x.v[0] + this->v[1] * x.v[1];
}

bool Vector::operator==(const Vector& x) const
{
	return this->v == x.v;
}

bool Vector::operator!=(const Vector& x) const
{
	return !(*this == x);
}

bool Vector::operator<(const Vector& x) const
{
	return (this->v[0] < x.v[0]) || (this->v[1] < x.v[1]);
}

bool Vector::operator>(const Vector& x) const
{
	return (this->v[0] > x.v[0] || (this->v[1] > x.v[1]));
}

Vector Vector::operator*(double x) const
{
	return Vector(this->v[0] * x, this->v[1] * x);
}

Vector& Vector::operator*=(double x)
{
	this->v[0] *= x;
	this->v[1] *= x;
	return *this;
}

Vector Vector::operator/(double x) const
{
	return Vector(this->v[0] / x, this->v[1] / x);
}

Vector& Vector::operator/=(double x)
{
	this->v[0] /= x;
	this->v[1] /= x;
	return *this;
}

double Vector::magnitude() const
{
	return std::sqrt(this->v[0] * this->v[0] + this->v[1] * this->v[1]);
}

Vector Vector::normalize() const
{
	const auto mag = this->magnitude();

	if(mag > 0.0)
	{
		return Vector(*this) / mag;
	}

	return Vector(*this);
}

double age::math::distance(const Vector& a, const Vector& b)
{
	return std::sqrt(std::pow(b.getX() - a.getX(), 2.0) + std::pow(b.getY() - a.getY(), 2.0));
}
