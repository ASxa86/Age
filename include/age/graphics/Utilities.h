#pragma once

#include <age/graphics/export.h>
#include <age/math/Vector.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace age
{
	namespace graphics
	{
		AGE_GRAPHICS_EXPORT age::math::Vector ToVector(const sf::Vector2f& x);
		AGE_GRAPHICS_EXPORT sf::Vector2f FromVector(const age::math::Vector& x);
		AGE_GRAPHICS_EXPORT sf::Color FromColor(const std::array<int, 4>& x);
	}
}