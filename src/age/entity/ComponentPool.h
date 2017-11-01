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

			virtual void init(std::size_t x) = 0;
			virtual void resize(std::size_t x) = 0;
			virtual std::size_t size() const = 0;
		};

		template <typename T>
		struct ComponentPool : public BasePool
		{
			void init(std::size_t x)
			{
				this->Components[x] = T();
			}

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
