#pragma once

#include <azule/export.hxx>
#include <azule/math/GLM.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace azule
{
	AZULE_EXPORT glm::vec2 ToVector(const sf::Vector2f& x);
	AZULE_EXPORT sf::Vector2f FromVector(const glm::vec2& x);
	AZULE_EXPORT sf::Color FromColor(const std::array<int, 4>& x);
}