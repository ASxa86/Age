#pragma once

#include <age/entity/Component.h>
#include <age/math/Export.h>
#include <boost/qvm/vec.hpp>

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
		class AGE_MATH_EXPORT TransformComponent : public age::entity::Component<TransformComponent>
		{
		public:
			TransformComponent();
			~TransformComponent();

			///
			///	Set the position for the component.
			///	(x, y)
			///
			void setPosition(const boost::qvm::vec<double, 2>& x);
			
			///
			///	Get the position for the component.
			///	(x, y)
			///
			boost::qvm::vec<double, 2> getPosition() const;

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
			boost::qvm::vec<double, 2> position;
			double rotation;
		};
	}
}
