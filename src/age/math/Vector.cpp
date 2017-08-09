#include <age/math/Vector.h>
#include <age/core/PimplImpl.h>

#include <array>

using namespace age::math;

class Vector::Impl
{
public:
	Impl() : v{}
	{
	}

	Impl(double x, double y) : v{x, y}
	{
	}

	std::array<double, 2> v;
};

Vector::Vector() : pimpl()
{
}

Vector::Vector(double x, double y) : pimpl(x, y)
{
}

Vector::Vector(const Vector& x) : Vector(x.x(), x.y())
{
}

Vector::~Vector()
{
}

double& Vector::x()
{
	return this->pimpl->v[0];
}

double& Vector::y()
{
	return this->pimpl->v[1];
}

double Vector::x() const
{
	return this->pimpl->v[0];
}

double Vector::y() const
{
	return this->pimpl->v[1];
}

Vector& Vector::operator=(const Vector& x)
{
	this->x() = x.x();
	this->y() = x.y();
	return *this;
}

Vector Vector::operator+(const Vector& x) const
{
	return Vector(this->x() + x.x(), this->y() + x.y());
}

Vector& Vector::operator+=(const Vector& x)
{
	this->x() += x.x();
	this->y() += x.y();
	return *this;
}

Vector Vector::operator-(const Vector& x) const
{
	return Vector(this->x() - x.x(), this->y() - x.y());
}

Vector& Vector::operator-=(const Vector& x)
{
	this->x() -= x.x();
	this->y() -= x.y();
	return *this;
}

double Vector::operator*(const Vector& x)
{
	return this->x() * x.x() + this->y() * x.y();
}

bool Vector::operator==(const Vector& x) const
{
	return (this->x() == x.x() && this->y() == x.y());
}

bool Vector::operator!=(const Vector& x) const
{
	return !(*this == x);
}

bool Vector::operator<(const Vector& x) const
{
	return (this->x() < x.x()) || (this->y() < x.y());
}

bool Vector::operator>(const Vector& x) const
{
	return (this->x() > x.x() || (this->y() > x.y()));
}

Vector Vector::operator*(double x) const
{
	return Vector(this->x() * x, this->y() * x);
}

Vector& Vector::operator*=(double x)
{
	this->x() *= x;
	this->y() *= x;
	return *this;
}

Vector Vector::operator/(double x) const
{
	return Vector(this->x() / x, this->y() / x);
}

Vector& Vector::operator/=(double x)
{
	this->x() /= x;
	this->y() /= x;
	return *this;
}

double Vector::magnitude() const
{
	return std::sqrt(this->x() * this->x() + this->y() * this->y());
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
