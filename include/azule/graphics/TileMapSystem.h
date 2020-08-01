#pragma once

#include <azule/export.hxx>
#include <azule/graphics/RenderSystem.h>

namespace azule
{
	class AZULE_EXPORT TileMapSystem : public RenderSystem
	{
	public:
		TileMapSystem();
		~TileMapSystem();

		void render(sf::RenderTarget& target, std::chrono::microseconds x) override;
	};
}
