#include <azule/graphics/Utilities.h>

glm::vec2 azule::ToVector(const sf::Vector2f& x)
{
	return {x.x, x.y};
}

sf::Vector2f azule::FromVector(const glm::vec2& x)
{
	return {static_cast<float>(x.x), static_cast<float>(x.y)};
}

sf::Color azule::FromColor(const std::array<int, 4>& x)
{
	return sf::Color{static_cast<sf::Uint8>(x[0]), static_cast<sf::Uint8>(x[1]), static_cast<sf::Uint8>(x[2]), static_cast<sf::Uint8>(x[3])};
}
