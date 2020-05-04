#pragma once

#include <age/graphics/DrawableComponent.h>
#include <age/math/Vector.h>
#include <SFML/Graphics/RectangleShape.hpp>

namespace age
{
	namespace graphics
	{
		class AGE_GRAPHICS_EXPORT ProgressBarComponent : public DrawableComponent
		{
		public:
			struct ProgressBar : sf::Drawable
			{
				void draw(sf::RenderTarget&, sf::RenderStates) const override;
				sf::RectangleShape fill;
				sf::RectangleShape outline;
			};

			double getPercentage() const;
			virtual const sf::Drawable* getDrawable() override;

			std::array<int, 4> Color{};
			age::math::Vector Position{};
			age::math::Vector Size{};
			int Value{0};
			int ValueMax{100};

		private:
			ProgressBar progressBar;
		};
	}
}
