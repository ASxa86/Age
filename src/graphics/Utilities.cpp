#include <azule/graphics/Utilities.h>

azule::Vector azule::ToVector(const sf::Vector2f& x)
{
	return {x.x, x.y};
}

sf::Vector2f azule::FromVector(const azule::Vector& x)
{
	return {static_cast<float>(x.X), static_cast<float>(x.Y)};
}

sf::Color azule::FromColor(const std::array<int, 4>& x)
{
	return sf::Color{static_cast<sf::Uint8>(x[0]), static_cast<sf::Uint8>(x[1]), static_cast<sf::Uint8>(x[2]), static_cast<sf::Uint8>(x[3])};
}
