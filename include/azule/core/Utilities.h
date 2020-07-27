#pragma once

#include <azule/core/export.h>

namespace azule
{
	namespace core
	{
		class Object;

		///
		///	Convert a given amount of pixels into meters based on the current configuration settings.
		///
		AZULE_CORE_EXPORT double PixelsToMeters(unsigned int x);

		AZULE_CORE_EXPORT std::unique_ptr<Object> Clone(Object* x);

		AZULE_CORE_EXPORT std::string ResolvePath(std::string x);
	}
}
