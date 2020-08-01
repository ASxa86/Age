#include <azule/utilities/String.h>
#include <azule/math/Vector.h>
#include <array>
#include <cmath>

using namespace azule;

Vector::Vector(double x, double y) : X{x}, Y{y}
{
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

double azule::distance(const Vector& a, const Vector& b)
{
	return std::sqrt(std::pow(b.X - a.X, 2.0) + std::pow(b.Y - a.Y, 2.0));
}

void azule::to_json(nlohmann::json& j, const Vector& x)
{
	j["x"] = x.X;
	j["y"] = x.Y;
}

void azule::from_json(const nlohmann::json& j, Vector& x)
{
	j["x"].get_to(x.X);
	j["y"].get_to(x.Y);
}
