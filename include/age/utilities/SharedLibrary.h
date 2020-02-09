#pragma once

//#include <age/utilities/Pimpl.h>
#include <age/utilities/export.h>
#include <filesystem>
#include <functional>

namespace age
{
	namespace utilities
	{
		///
		///	\class SharedLibrary
		///
		///	\brief Modeled after boost's boost::dll::shared_library.
		///
		///	This class uses RAII to load and keep loaded a shared library.
		///
		///	\author Aaron Shelley
		///
		///	\date February 8, 2020
		///
		class AGE_UTILITIES_EXPORT SharedLibrary
		{
		public:
			SharedLibrary() = default;
			SharedLibrary(const std::filesystem::path& x);
			~SharedLibrary();

			///
			///	\brief Performing a copy will increment a reference count to this library.
			///
			///	Once all copies have been destroyed, the library will be unloaded.
			///
			SharedLibrary(const SharedLibrary& x);

			///
			///	\brief Performing a copy will increment a reference count to this library.
			///
			///	Once all copies have been destroyed, the library will be unloaded.
			///
			SharedLibrary& operator=(const SharedLibrary& x);

			///
			///	Loads a library by specified path with a specified mode.
			///
			///	Note that if some library is already loaded in this instance, load will
			///	call unload() and then load the new provided library.
			///
			///	\param x Library file name.
			///	\return true if the library was successfully loaded.
			///
			[[maybe_unused]] bool load(const std::filesystem::path& x);

			///
			///	\brief Unloads a shared library.
			///
			///	If library was loaded multiple times by different instances,
			///	the actual DLL / DSO won't be unloaded until there is at least
			///	one instance that references the DLL / DSO.
			///
			void unload();

			///
			///	\brief Check if the library is loaded.
			///
			///	\return true if the library was succesfully loaded.
			///
			bool loaded() const;

			///
			///	\brief Get a function symbol within the library for a give symbol name.
			///
			///	\param x The symbol name to look up in the library.
			///	\return std::function<void()> if the given symbol name exists.
			///
			std::function<void()> symbol(const std::string& x) const;

			///
			///	\return Returns the file path to the loaded library.
			///
			std::filesystem::path location() const;

		private:
			std::filesystem::path loc;
			void* handle{nullptr};
		};
	}
}
