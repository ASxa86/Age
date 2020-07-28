#pragma once

#include <azule/export.h>
#include <azule/math/Vector.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace azule
{
	namespace graphics
	{
		AZULE_EXPORT azule::math::Vector ToVector(const sf::Vector2f& x);
		AZULE_EXPORT sf::Vector2f FromVector(const azule::math::Vector& x);
		AZULE_EXPORT sf::Color FromColor(const std::array<int, 4>& x);
	}
}