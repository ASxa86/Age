#pragma once

#include <age/core/Pimpl.h>
#include <age/physics/Export.h>
#include <boost/qvm/vec.hpp>

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
			void setCenter(const boost::qvm::vec<double, 2>& x);
			boost::qvm::vec<double, 2> getCenter() const;

			///
			///	Set the size of the box (x:width, y:height).
			///
			void setSize(const boost::qvm::vec<double, 2>& x);
			boost::qvm::vec<double, 2> getSize() const;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
