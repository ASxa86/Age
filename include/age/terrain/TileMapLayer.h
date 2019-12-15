#pragma once

#include <age/terrain/export.h>
#include <string>
#include <vector>

namespace age
{
	namespace terrain
	{
		///
		///	\class TileMapLayer
		///
		///	\brief This class represents a single layer for a tile map.
		///
		///	\date October 20, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_TERRAIN_EXPORT TileMapLayer
		{
		public:
			TileMapLayer();
			~TileMapLayer();

			///
			///	\brief Name identifier for this layer.
			///
			void setName(const std::string& x);
			std::string getName() const;

			///
			///	\brief The number of horizontal columns in this layer.
			///
			void setWidth(int x);
			int getWidth() const;

			///
			///	\brief The number of vertical rows in this layer.
			///
			void setHeight(int x);
			int getHeight() const;

			///
			///	\brief The list of indices found in this layer that reference a tile index.
			///
			void setIndices(const std::vector<int>& x);
			const std::vector<int>& getIndices() const;

		private:
			std::vector<int> indices;
			std::string name;
			int width;
			int height;
		};
	}
}
