#pragma once

#include <azule/graphics/DrawableComponent.h>
#include <azule/math/GLM.h>
#include <SFML/Graphics/RectangleShape.hpp>

namespace azule
{
	class AZULE_EXPORT ProgressBarComponent : public DrawableComponent
	{
	public:
		struct ProgressBar : sf::Drawable
		{
			void draw(sf::RenderTarget&, sf::RenderStates) const override;
			sf::RectangleShape fill;
			sf::RectangleShape outline;
		};

		ProgressBarComponent();

		double getPercentage() const;
		virtual const sf::Drawable* getDrawable() override;

		std::array<int, 4> Color{};
		glm::vec2 Position{};
		glm::vec2 Size{};
		int Value{0};
		int ValueMax{100};

	private:
		ProgressBar progressBar;
	};
}
