#pragma once

#include <azule/entity/SelectionComponent.h>
#include <azule/export.hxx>
#include <azule/math/GLM.h>
#include <SFML/Graphics/RectangleShape.hpp>

namespace azule
{
	class DrawableSystem;

	class AZULE_EXPORT BoxSelectionComponent : public azule::SelectionComponent
	{
	public:
		BoxSelectionComponent();

		glm::vec2 Size{};
		std::array<int, 4> FillColor{};
		std::array<int, 4> OutlineColor{};
		double OutlineThickness{};

	private:
		friend class DrawableSystem;
		friend class RenderSystem;
		sf::RectangleShape Shape;
	};
}
