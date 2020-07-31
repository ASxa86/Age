#pragma once

#include <azule/export.h>

namespace azule
{
	class Object;

	///
	///	Convert a given amount of pixels into meters based on the current configuration settings.
	///
	AZULE_EXPORT double PixelsToMeters(unsigned int x);

	AZULE_EXPORT std::unique_ptr<Object> Clone(Object* x);

	AZULE_EXPORT std::string ResolvePath(std::string x);
}
