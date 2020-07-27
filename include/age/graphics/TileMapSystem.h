#pragma once

#include <age/graphics/export.h>
#include <age/graphics/RenderSystem.h>

namespace age
{
	namespace graphics
	{
		class AGE_GRAPHICS_EXPORT TileMapSystem : public RenderSystem
		{
		public:
			TileMapSystem();
			~TileMapSystem();

			void render(sf::RenderTarget& target, std::chrono::microseconds x) override;
		};
	}
}
