#pragma once

namespace age
{
	namespace entity
	{
		struct BaseComponent
		{
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
