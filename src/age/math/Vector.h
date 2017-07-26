#pragma once

#include <age/math/Export.h>
#include <age/core/Pimpl.h>

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
			Vector();
			Vector(double x, double y);
			Vector(const Vector& x);
			~Vector();

			double& x();
			double& y();

			double x() const;
			double y() const;

			Vector& operator=(const Vector& x);
			Vector operator+(const Vector& x);
			Vector& operator+=(const Vector& x);
			Vector operator-(const Vector& x);
			Vector& operator-=(const Vector& x);
			double operator*(const Vector& x);

			bool operator==(const Vector& x) const;
			bool operator!=(const Vector& x) const;
			bool operator<(const Vector& x) const;
			bool operator>(const Vector& x) const;

			Vector operator*(double x);
			Vector& operator*=(double x);
			Vector operator/(double x);
			Vector& operator/=(double x);

			double magnitude() const;
			double normalize();

			template<typename T, typename ValueType = double>
			static T To(const Vector& x)
			{
				return T{static_cast<ValueType>(x.x()), static_cast<ValueType>(x.y())};
			}

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
