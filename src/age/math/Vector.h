#pragma once

#include <age/math/Export.h>
#include <array>

namespace age
{
	namespace math
	{
		///
		///	\class Vector
		///
		///	\brief This class represents a vector.
		///
		///	\date June 20, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_MATH_EXPORT Vector
		{
		public:
			///
			///	Operator overloads.
			///
			Vector operator+(const Vector& x) const;
			Vector& operator+=(const Vector& x);
			Vector operator-(const Vector& x) const;
			Vector& operator-=(const Vector& x);

			///
			///	Dot product.
			///
			double operator*(const Vector& x) const;

			///
			///	Comparator operator overloads
			///
			bool operator==(const Vector& x) const;
			bool operator!=(const Vector& x) const;
			bool operator<(const Vector& x) const;
			bool operator>(const Vector& x) const;

			///
			///	Scalar operator overloads.
			///
			Vector operator*(double x) const;
			Vector& operator*=(double x);
			Vector operator/(double x) const;
			Vector& operator/=(double x);

			double magnitude() const;
			double normalize();

			double X;
			double Y;
		};

		AGE_MATH_EXPORT double distance(const Vector& a, const Vector& b);
		AGE_MATH_EXPORT std::ostream& operator<<(std::ostream& os, Vector x);
		AGE_MATH_EXPORT std::istream& operator>>(std::istream& is, Vector& x);
	}
}
