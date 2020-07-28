#pragma once

#include <azule/core/Object.h>
#include <azule/utilities/Pimpl.h>
#include <filesystem>

namespace azule
{
	namespace core
	{
		///
		///	\class Parser
		///
		///	\brief Base class parser to be dervied in order to handle special file formats.
		///
		///	Derive from this class and register the derived class with the factory in order to
		///	add a file format for ReadFile() to support.
		///
		///	\date October 20, 2018
		///
		///	\author Aaron Shelley
		///
		class AZULE_EXPORT Parser : public Object
		{
		public:
			Parser();
			virtual ~Parser();

			///
			///	\brief Parse the given file format.
			///
			///	\param obj The object to load data into. This parameter is optional, if no object is given, the parser may return its own object.
			///
			virtual bool readFile(const std::filesystem::path& x, Object* obj);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};

		///
		///	\brief Function for generically loading file formats into the given object.
		///
		AZULE_EXPORT bool ReadFile(const std::filesystem::path& x, Object* obj);
	}
}
