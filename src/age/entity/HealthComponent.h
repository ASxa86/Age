#pragma once

#include <age/entity/Component.h>

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT HealthComponent : public Component
		{
		public:
			HealthComponent();

			double getPercentage() const;

			int Health{0};
			int HealthMax{100};
		};
	}
}
