#pragma once

#include <azule/export.hxx>
#include <filesystem>

namespace azule
{
	///
	///	\class TileSource
	///
	///	\brief This class describes a single source file and description.
	///
	///	\date October 20, 2018
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT TileSource
	{
	public:
		TileSource();
		~TileSource();

		///
		///	\brief The file name of the source.
		///
		void setFileName(const std::filesystem::path& x);
		const std::filesystem::path& getFileName() const;

		///
		///	\brief The width of the source file in pixels.
		///
		void setWidth(int x);
		int getWidth() const;

		///
		///	\brief The height of the source file in pixels.
		///
		void setHeight(int x);
		int getHeight() const;

	private:
		std::filesystem::path fileName;
		int width;
		int height;
	};
}
