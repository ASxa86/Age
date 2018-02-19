#pragma once

#include <age/graphics/RenderSystem.h>

namespace age
{
	namespace graphics
	{
		class AGE_GRAPHICS_EXPORT SpriteAnimationSystem : public RenderSystem
		{
			SpriteAnimationSystem();
			~SpriteAnimationSystem() override;

			void render(sf::RenderTarget& target, sf::RenderStates& state, std::chrono::microseconds);
		};
	}
}
