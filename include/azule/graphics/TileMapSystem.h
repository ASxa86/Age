#pragma once

#include <azule/graphics/export.h>
#include <azule/graphics/RenderSystem.h>

namespace azule
{
	namespace graphics
	{
		class AZULE_GRAPHICS_EXPORT TileMapSystem : public RenderSystem
		{
		public:
			TileMapSystem();
			~TileMapSystem();

			void render(sf::RenderTarget& target, std::chrono::microseconds x) override;
		};
	}
}
