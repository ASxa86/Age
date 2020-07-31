#pragma once

#include <azule/core/Object.h>
#include <azule/export.h>

namespace azule
{
	class AZULE_EXPORT Component : public azule::Object
	{
	public:
		bool Enabled{true};

	private:
	};
}
