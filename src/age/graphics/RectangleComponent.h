#pragma once

#include <age/graphics/DrawableComponent.h>
#include <array>

namespace age
{
	namespace graphics
	{
		///
		///	\class RectangleComponent
		///
		///	\brief A drawable rectangle component.
		///
		///	\date June 9, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT RectangleComponent : public DrawableComponent
		{
		public:
			RectangleComponent();
			~RectangleComponent() override;

			///
			///	Set the size of the rectangle. (x, y).
			///
			void setSize(const std::array<double, 2>& x);

			///
			///	Get the size of the rectangle. (x, y).
			///
			std::array<double, 2> getSize() const;

			void draw(sf::RenderTarget& x, unsigned int pixelsPerMeter) override;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}