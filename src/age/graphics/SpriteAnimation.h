#pragma once

#include <age/graphics/Export.h>
#include <chrono>
#include <utility>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>

namespace age
{
	namespace graphics
	{
		class AGE_GRAPHICS_EXPORT SpriteAnimation
		{
		public:
			SpriteAnimation();
			~SpriteAnimation();

			void addSprite(std::chrono::microseconds, const sf::Sprite& x);
			sf::Sprite& getCurrentSprite();
			std::chrono::microseconds getCurrentTime() const;

			void setElapsedTime(std::chrono::microseconds x);
			std::chrono::microseconds getElapsedTime() const;

			void setNextFrame();

		private:
			std::vector<std::pair<std::chrono::microseconds, sf::Sprite>> sprites;
			std::chrono::microseconds elapsedTime;
			int currentIndex;
		};
	}
}
