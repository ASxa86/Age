#include <age/math/Vector.h>
#include <array>

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

double Vector::operator*(const Vector& x)
{
	return this->v[0] * x.v[0] + this->v[1] * x.v[1];
}

bool Vector::operator==(const Vector& x) const
{
	return (this->v[0] == x.v[0] && this->v[1] == x.v[1]);
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

double Vector::normalize()
{
	const auto mag = this->magnitude();

	if(mag > 0.0)
	{
		*this /= mag;
	}

	return mag;
}
