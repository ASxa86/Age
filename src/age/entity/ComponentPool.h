#pragma once

#include <vector>

namespace age
{
	namespace entity
	{
		struct BasePool
		{
			virtual ~BasePool()
			{
			}

			virtual void resize(std::size_t x) = 0;
			virtual std::size_t size() const = 0;
		};

		template <typename T>
		struct ComponentPool : public BasePool
		{
			void resize(std::size_t x) override
			{
				this->Components.resize(x);
			}

			std::size_t size() const
			{
				return this->Components.size();
			}

			std::vector<T> Components;
		};
	}
}
