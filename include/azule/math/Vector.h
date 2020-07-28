#pragma once

#include <azule/export.h>
#include <array>
#include <string>

namespace azule
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
		class AZULE_EXPORT Vector
		{
		public:
			Vector(double x = 0.0, double y = 0.0);
			Vector(const std::string& x);
			operator std::string() const;
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

		AZULE_EXPORT double distance(const Vector& a, const Vector& b);
	}
}
