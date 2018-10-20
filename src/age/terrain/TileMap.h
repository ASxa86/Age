#pragma once

#include <age/terrain/Export.h>
#include <age/terrain/TileMapLayer.h>
#include <filesystem>

namespace age
{
	namespace terrain
	{
		///
		///	\class TileMap
		///
		///	\brief A tile map that consists of multiple tile layers built with tile set references.
		///
		///	\date October 20, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_TERRAIN_EXPORT TileMap
		{
		public:
			TileMap();
			~TileMap();

			///
			///	\brief Add a layer to the tile map.
			///	Layers can be used to render tile map in customized orders.
			///
			void addLayer(const TileMapLayer& x);
			const std::vector<TileMapLayer>& getLayers() const;

			///
			///	\brief Defines the overall tile map grid width with the number of tiles.
			///
			void setWidth(int x);
			int getWidth() const;

			///
			///	\brief Defines the overall tile map grid height with the number of tiles.
			///
			void setHeight(int x);
			int getHeight() const;

			///
			///	\brief The width of a single tile in pixels.
			///
			void setTileHeight(int x);
			int getTileHeight() const;

			///
			///	\brief The height of a single tile in pixels.
			///
			void setTileWidth(int x);
			int getTileWidth() const;

		private:
			std::vector<TileMapLayer> layers;
			int width;
			int height;
			int tileWidth;
			int tileHeight;
		};
	}
}
