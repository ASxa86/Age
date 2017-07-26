#pragma once

#include <age/core/Object.h>
#include <age/math/Vector.h>

namespace age
{
	namespace math
	{
		///
		///	\class TransformComponent
		///
		///	\brief This component is given to entities that hold a position within the scene.
		///
		///	\date June 11, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_MATH_EXPORT TransformComponent : public age::core::Object
		{
		public:
			TransformComponent();
			~TransformComponent() override;

			///
			///	Set the position for the component.
			///	(x, y)
			///
			void setPosition(const Vector& x);
			
			///
			///	Get the position for the component.
			///	(x, y)
			///
			Vector getPosition() const;

			///
			///	Set the rotation for the component.
			///	(Degrees)
			///
			void setRotation(double x);

			///
			///	Get the rotation for the component.
			///	(Degrees)
			///
			double getRotation() const;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
