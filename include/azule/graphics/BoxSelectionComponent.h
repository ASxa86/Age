#pragma once

#include <azule/entity/SelectionComponent.h>
#include <azule/export.h>
#include <azule/math/Vector.h>
#include <SFML/Graphics/RectangleShape.hpp>

namespace azule
{
	class DrawableSystem;

	class AZULE_EXPORT BoxSelectionComponent : public azule::SelectionComponent
	{
	public:
		BoxSelectionComponent();

		azule::Vector Size{};
		std::array<int, 4> FillColor{};
		std::array<int, 4> OutlineColor{};
		double OutlineThickness{};

	private:
		friend class DrawableSystem;
		friend class RenderSystem;
		sf::RectangleShape Shape;
	};
}
