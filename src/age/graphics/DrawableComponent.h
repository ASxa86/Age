#pragma once

#include <age/core/Object.h>
#include <age/graphics/Export.h>

namespace sf
{
	class RenderTarget;
	class Transformable;
}

namespace age
{
	namespace graphics
	{
		///
		///	\class DrawableComponent
		///
		///	\brief An abstract component to manage rendering derived components data objects.
		///
		///	\date June 5, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT DrawableComponent : public age::core::Object
		{
		public:
			DrawableComponent();
			virtual ~DrawableComponent() override;

			///
			///	\brief Override to handle drawing the derived component's data.
			///
			virtual void draw(sf::RenderTarget& x, unsigned int pixelsPerMeter) = 0;

		protected:
			///
			///	\brief Conveniences function for updating a drawable's transformation with its entity's transform component.
			///
			void updateTransform(sf::Transformable& x, unsigned int pixelsPerMeter);
		};
	}
}
