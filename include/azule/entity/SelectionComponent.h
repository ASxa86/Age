#pragma once

#include <azule/entity/Component.h>

namespace azule
{
	namespace entity
	{
		class AZULE_EXPORT SelectionComponent : public Component
		{
		public:
			SelectionComponent();

			bool Selected{false};
		};
	}
}
