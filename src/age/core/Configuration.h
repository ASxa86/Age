#pragma once

#include <age/core/Export.h>
#include <age/core/Pimpl.h>
#include <filesystem>

namespace age
{
	namespace core
	{
		///
		///	\class Configuration
		///
		///	\brief Global configuration settings for AGE.
		///
		///	\date July 8, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Configuration
		{
		public:
			Configuration(const Configuration&) = delete;
			Configuration& operator=(const Configuration&) = delete;

			///
			///	Singleton
			///	Loads configuration files and finds relative data paths.
			///
			static const Configuration& Instance();

			///
			///	Get the full path to AGE's data directory.
			///
			std::filesystem::path getDataPath() const;

			///
			///	Set the pixels per meter unit scaling for drawable objects.
			///	(32 pixels per meter)
			///
			void setPixelsPerMeter(unsigned int x);

			///
			///	Get the pixels per meter unit scaling.
			///
			unsigned int getPixelsPerMeter() const;

		private:
			Configuration();

			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
