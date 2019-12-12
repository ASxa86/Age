#include <age/core/String.h>
#include <age/math/Vector.h>
#include <array>
#include <cmath>

using namespace age::math;

std::ostream& age::math::operator<<(std::ostream& os, Vector x)
{
	os << "{" << x.X << ", " << x.Y << "}";
	return os;
}

std::istream& age::math::operator>>(std::istream& is, Vector& x)
{
	std::string temp;
	std::getline(is, temp);

	const auto tokens = age::core::Split(temp);

	if(tokens.size() == 2)
	{
		x.X = age::core::StringTo<double>(tokens[0]);
		x.Y = age::core::StringTo<double>(tokens[1]);
	}

	return is;
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
