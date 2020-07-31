#pragma once

#include <azule/export.h>
#include <azule/math/Vector.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace azule
{
	AZULE_EXPORT azule::Vector ToVector(const sf::Vector2f& x);
	AZULE_EXPORT sf::Vector2f FromVector(const azule::Vector& x);
	AZULE_EXPORT sf::Color FromColor(const std::array<int, 4>& x);
}