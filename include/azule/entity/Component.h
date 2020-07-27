#pragma once

#include <azule/core/Object.h>
#include <azule/entity/export.h>

namespace azule
{
	namespace entity
	{
		class AZULE_ENTITY_EXPORT Component : public azule::core::Object
		{
		public:
			bool Enabled{true};

		private:
		};
	}
}
