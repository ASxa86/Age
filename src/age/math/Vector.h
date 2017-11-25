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
			///	Constructor.
			///
			Vector();
			
			///
			///	Constructor
			///
			///	\param x The x component.
			///	\param y The y component.
			///
			Vector(double x, double y);

			///
			///	Destructor
			///
			~Vector();

			///
			///	Set the x component.
			///
			void setX(double x);
			double getX() const;

			///
			///	Set the y component.
			///
			void setY(double x);
			double getY() const;

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
			double operator*(const Vector& x);

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

			///
			///	Convenience function to convert from a Vector to a 3rd party vector type.
			///
			template<typename T, typename ValueType = double>
			static T To(const Vector& x)
			{
				return T{static_cast<ValueType>(x.v[0]), static_cast<ValueType>(x.v[1])};
			}

		private:
			std::array<double, 2> v;
		};
	}
}
