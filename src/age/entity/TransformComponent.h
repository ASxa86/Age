#pragma once

#include <age/entity/Export.h>
#include <age/math/Vector.h>

namespace age
{
	namespace entity
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
		class AGE_ENTITY_EXPORT TransformComponent
		{
		public:
			TransformComponent();
			~TransformComponent();

			///
			///	Set the position for the component.
			///	(x, y)
			///
			void setPosition(const age::math::Vector& x);

			///
			///	Get the position for the component.
			///	(x, y)
			///
			age::math::Vector getPosition() const;

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
			age::math::Vector position;
			double rotation;
		};
	}
}
