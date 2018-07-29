#pragma once

#include <age/core/Export.h>

namespace age
{
	namespace core
	{
		///
		///	Convert a given amount of pixels into meters based on the current configuration settings.
		///
		AGE_CORE_EXPORT double PixelsToMeters(unsigned int x);
	}
}
