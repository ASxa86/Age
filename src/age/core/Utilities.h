#pragma once

#include <age/core/Export.h>

namespace age
{
	namespace core
	{
		class Object;

		///
		///	Convert a given amount of pixels into meters based on the current configuration settings.
		///
		AGE_CORE_EXPORT double PixelsToMeters(unsigned int x);

		AGE_CORE_EXPORT std::unique_ptr<Object> Clone(Object* x);
	}
}
