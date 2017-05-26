#pragma once

#include <age/core/Object.h>
#include <age/graphics/Export.h>
#include <SFML/Graphics/Sprite.hpp>

namespace age
{
	namespace graphics
	{
		///
		///	\class SpriteComponent
		///
		///	\brief This class is a Component in the Entity Component System. Maintains the state of an SFML sprite object.
		///
		///	\date May 25, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT SpriteComponent : public age::core::Object
		{
		public:
			SpriteComponent();
			virtual ~SpriteComponent();

			///
			///	Set the sprite for this component.
			///
			void setSprite(const sf::Sprite& x);

			///
			///	Get the sprite for this component.
			///
			sf::Sprite getSprite() const;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
