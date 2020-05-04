#pragma once

#include <age/entity/Component.h>
#include <age/graphics/export.h>
#include <SFML/Graphics/Drawable.hpp>

namespace age
{
	namespace graphics
	{
		///
		///	\class DrawableComponent
		///
		///	\brief This class manages a single SFML drawable and any related configurations for it.
		///
		///	\author Aaron Shelley
		///
		///	\date May 3, 2020
		///
		class AGE_GRAPHICS_EXPORT DrawableComponent : public age::entity::Component
		{
		public:
			virtual const sf::Drawable* getDrawable();

			///
			///	Used to determine the order of drawing all drawable components during the render process.
			///
			int RenderOrder{0};

			///
			///	Apply the rotation of the TransformationComponent in addition to any rotations provided by the drawable.
			///
			bool UseRotation{false};

			///
			///	Apply the position of the TransformationComponent in addition to any position provided by the drawable.
			///
			bool UsePosition{true};
		};
	}
}