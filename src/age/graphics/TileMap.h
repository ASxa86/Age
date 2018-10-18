#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <filesystem>

namespace age
{
	namespace graphics
	{
		class TileMap
		{
		public:
			struct Layer
			{
				std::vector<std::vector<int>> Tiles{};
				std::string Name{};
			};

			TileMap();
			~TileMap();

			void addLayer(const Layer& x);
			const std::vector<Layer>& getLayers() const;

			void setWidth(int x);
			int getWidth() const;

			void setHeight(int x);
			int getHeight() const;

			void setTileHeight(int x);
			int getTileHeight() const;

			void setTileWidth(int x);
			int getTileWidth() const;

		private:
			std::vector<Layer> layers;
			int width;
			int height;
			int tileWidth;
			int tileHeight;
		};
	}
}
