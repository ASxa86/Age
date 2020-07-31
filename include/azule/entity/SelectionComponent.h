#pragma once

#include <azule/entity/Component.h>

namespace azule
{
	class AZULE_EXPORT SelectionComponent : public Component
	{
	public:
		SelectionComponent();

		bool Selected{false};
	};
}
