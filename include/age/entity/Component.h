#pragma once

#include <age/core/Object.h>
#include <age/entity/export.h>

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT Component : public age::core::Object
		{
		public:
			bool Enabled{true};

		private:
		};
	}
}
