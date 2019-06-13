#include <age/core/Utilities.h>

#include <age/core/Configuration.h>

double age::core::PixelsToMeters(unsigned int x)
{
	return static_cast<double>(x) / static_cast<double>(age::core::Configuration::Instance().getPixelsPerMeter());
}
