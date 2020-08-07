#pragma once

#include <azule/core/Object.h>
#include <azule/export.hxx>

namespace azule
{
	class AZULE_EXPORT Component : public azule::Object
	{
	public:
		Component();
		bool Enabled{true};

	private:
	};
}
