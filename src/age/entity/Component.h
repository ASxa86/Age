#pragma once

#include <age/entity/Export.h>

namespace age
{
	namespace entity
	{
		struct AGE_ENTITY_EXPORT BaseComponent
		{
			BaseComponent();
			BaseComponent(const BaseComponent&) = delete;
			BaseComponent& operator=(const BaseComponent&) = delete;

			static unsigned int counter;
		};

		template <typename T>
		struct Component : public BaseComponent
		{
			static unsigned int index()
			{
				static unsigned int index = BaseComponent::counter++;
				return index;
			}
		};
	}
}
