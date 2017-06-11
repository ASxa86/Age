#pragma once

#include <age/core/Object.h>
#include <array>

namespace age
{
	namespace core
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
		class AGE_CORE_EXPORT TransformComponent : public Object
		{
		public:
			TransformComponent();
			~TransformComponent() override;

			///
			///	Set the position for the component.
			///	(x, y)
			///
			void setPosition(const std::array<double, 2>& x);
			
			///
			///	Get the position for the component.
			///	(x, y)
			///
			std::array<double, 2> getPosition() const;

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
