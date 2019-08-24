#pragma once

#include <age/entity/Component.h>

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT SelectionComponent : public Component
		{
		public:
			SelectionComponent();

			bool Selected{false};
		};
	}
}
