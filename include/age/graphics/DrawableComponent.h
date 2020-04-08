#pragma once

#include <age/entity/Component.h>
#include <SFML/Graphics/Drawable.hpp>

namespace age
{
	namespace graphics
	{
		class DrawableComponent : public age::entity::Component
		{
		public:
			virtual sf::Drawable& getDrawable() = 0;
		};
	}
}