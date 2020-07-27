#pragma once

#include <age/terrain/export.h>
#include <age/terrain/TileSource.h>
#include <filesystem>

namespace age
{
	namespace terrain
	{
		///
		///	\class TileSet
		///
		///	\brief This class describes a tile set.
		///
		///	\date October 20, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_TERRAIN_EXPORT TileSet
		{
		public:
			TileSet();
			~TileSet();

			///
			///	\brief An identifier name for this tile set.
			///
			void setName(const std::string& x);
			const std::string& getName() const;

			///
			///	\brief Defines a tile id offset for tile indexing.
			///
			void setTileOffset(int x);
			int getTileOffset() const;

			///
			///	\brief The width of a single tile found within this tile set in pixels.
			///
			void setTileWidth(int x);
			int getTileWidth() const;

			///
			///	\brief The height of a single tile found within this tile set in pixels.
			///
			void setTileHeight(int x);
			int getTileHeight() const;

			///
			///	\brief The spacing found between tiles in pixels.
			///
			void setSpacing(int x);
			int getSpacing() const;

			///
			///	\brief The total number of tiles this tile set is made up of.
			///
			void setTileCount(int x);
			int getTileCount() const;

			///
			///	\brief The number of columns this tile set is made up of.
			///
			void setColumns(int x);
			int getColumns() const;

			///
			///	\brief The source data for this tile set.
			///
			void setSource(const TileSource& x);
			const TileSource& getSource() const;

		private:
			TileSource source;
			std::string name;
			int tileOffset;
			int tileCount;
			int columns;
			int tileWidth;
			int tileHeight;
			int spacing;
		};
	}
}
