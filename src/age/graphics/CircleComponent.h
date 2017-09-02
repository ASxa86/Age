#pragma once

#include <age/graphics/DrawableComponent.h>

namespace age
{
	namespace graphics
	{
		///
		///	\class CircleComponent
		///
		///	\brief This component is a drawable circle.
		///
		///	\date June 13, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT CircleComponent : public DrawableComponent
		{
		public:
			CircleComponent();
			~CircleComponent() override;

			///
			///	Set the radius for the circle.
			///	(pixels)
			///
			void setRadius(double x);

			///
			///	Get the radius for the circle.
			///	(pixels)
			///
			double getRadius() const;

			///
			///	Handle drawing this component's shape.
			///
			void draw(sf::RenderTarget& x, unsigned int pixelsPerMeter) override;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
