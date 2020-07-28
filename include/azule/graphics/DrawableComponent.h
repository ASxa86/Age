#pragma once

#include <azule/entity/Component.h>
#include <azule/export.h>
#include <SFML/Graphics/Drawable.hpp>

namespace azule
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
		class AZULE_EXPORT DrawableComponent : public azule::entity::Component
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