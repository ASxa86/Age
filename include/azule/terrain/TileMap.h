#pragma once

#include <azule/terrain/export.h>
#include <azule/terrain/TileMapLayer.h>
#include <azule/terrain/TileSet.h>
#include <filesystem>

namespace azule
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
		class AZULE_TERRAIN_EXPORT TileMap
		{
		public:
			TileMap();
			virtual ~TileMap();

			///
			///	\brief Add a layer to the tile map.
			///	Layers can be used to render tile map in customized orders.
			///
			void addLayer(const TileMapLayer& x);
			const std::vector<TileMapLayer>& getLayers() const;

			///
			///	\brief Add a tile set for this map to refrence tile indices from.
			///
			void addTileSet(const TileSet& x);
			const std::vector<TileSet>& getTileSet() const;

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
			///	\brief The height of a single tile in pixels.
			///
			void setTileHeight(int x);
			int getTileHeight() const;

			///
			///	\brief The width of a single tile in pixels.
			///
			void setTileWidth(int x);
			int getTileWidth() const;

		private:
			std::vector<TileMapLayer> layers;
			std::vector<TileSet> tileSets;
			int width;
			int height;
			int tileWidth;
			int tileHeight;
		};
	}
}
