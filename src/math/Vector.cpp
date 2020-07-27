#include <age/utilities/String.h>
#include <age/math/Vector.h>
#include <array>
#include <cmath>

using namespace age::math;

Vector::Vector(double x, double y) : X{x}, Y{y}
{
}

Vector::Vector(const std::string& x)
{
	const auto tokens = age::utilities::Split(x);

	if(tokens.size() == 2)
	{
		this->X = age::utilities::StringTo<double>(tokens[0]);
		this->Y = age::utilities::StringTo<double>(tokens[1]);
	}
}

Vector::operator std::string() const
{
	return "{" + age::utilities::ToString(this->X) + ", " + age::utilities::ToString(this->Y) + "}";
}

Vector Vector::operator+(const Vector& x) const
{
	return Vector{this->X + x.X, this->Y + x.Y};
}

Vector& Vector::operator+=(const Vector& x)
{
	this->X += x.X;
	this->Y += x.Y;
	return *this;
}

Vector Vector::operator-(const Vector& x) const
{
	return Vector{this->X - x.X, this->Y - x.Y};
}

Vector& Vector::operator-=(const Vector& x)
{
	this->X -= x.X;
	this->Y -= x.Y;
	return *this;
}

double Vector::operator*(const Vector& x) const
{
	return this->X * x.X + this->Y * x.Y;
}

bool Vector::operator==(const Vector& x) const
{
	return this->X == x.X && this->Y == x.Y;
}

bool Vector::operator!=(const Vector& x) const
{
	return !(*this == x);
}

bool Vector::operator<(const Vector& x) const
{
	return (this->X < x.X) || (this->Y < x.Y);
}

bool Vector::operator>(const Vector& x) const
{
	return (this->X > x.X || (this->Y > x.Y));
}

Vector Vector::operator*(double x) const
{
	return Vector{this->X * x, this->Y * x};
}

Vector& Vector::operator*=(double x)
{
	this->X *= x;
	this->Y *= x;
	return *this;
}

Vector Vector::operator/(double x) const
{
	return Vector{this->X / x, this->Y / x};
}

Vector& Vector::operator/=(double x)
{
	this->X /= x;
	this->Y /= x;
	return *this;
}

double Vector::magnitude() const
{
	return std::sqrt(this->X * this->X + this->Y * this->Y);
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

double age::math::distance(const Vector& a, const Vector& b)
{
	return std::sqrt(std::pow(b.X - a.X, 2.0) + std::pow(b.Y - a.Y, 2.0));
}
