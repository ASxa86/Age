#pragma once

#include <age/math/Vector.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		///
		///	\class BoxCollisionComponent
		///
		///	\brief A box collision component for determining if this object collides with another.
		///
		///	\date July 28, 2017
		///
		///	\date Aaron Shelley
		///
		class AGE_PHYSICS_EXPORT BoxCollisionComponent
		{
		public:
			BoxCollisionComponent();
			~BoxCollisionComponent();

			///
			///	Set the center of this collision component. This is an offset to the entity it is attached to.
			///
			void setCenter(const age::math::Vector& x);
			age::math::Vector getCenter() const;

			///
			///	Set the size of the box (x:width, y:height).
			///
			void setSize(const age::math::Vector& x);
			age::math::Vector getSize() const;

		private:
			age::math::Vector center;
			age::math::Vector size;
		};
	}
}
