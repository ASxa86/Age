#pragma once

#include <age/entity/SelectionComponent.h>
#include <age/graphics/Export.h>
#include <age/math/Vector.h>
#include <SFML/Graphics/RectangleShape.hpp>

namespace age
{
	namespace graphics
	{
		class DrawableSystem;

		class AGE_GRAPHICS_EXPORT BoxSelectionComponent : public age::entity::SelectionComponent
		{
		public:
			BoxSelectionComponent();

			age::math::Vector Size{};
			std::array<int, 4> FillColor{};
			std::array<int, 4> OutlineColor{};
			double OutlineThickness{};

		private:
			friend class DrawableSystem;
			sf::RectangleShape Shape;
		};
	}
}
