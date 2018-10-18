#pragma once

#include <age/core/Object.h>
#include <filesystem>

namespace age
{
	namespace core
	{
		class AGE_CORE_EXPORT Parser : public Object
		{
		public:
			Parser();
			virtual ~Parser();

			virtual std::shared_ptr<Object> readFile(const std::filesystem::path& x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};

		AGE_CORE_EXPORT std::shared_ptr<Object> ReadFile(const std::filesystem::path& x);
	}
}
