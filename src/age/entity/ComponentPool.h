#pragma once

#include <age/entity/Export.h>
#include <bitset>
#include <vector>

namespace age
{
	namespace entity
	{
		///
		///	\class BasePool
		///
		///	\brief Essentially a wrapper around an stl container.
		///
		///	This is what makes fast/efficient entity iteration possible.
		///
		///	\date July 14, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_ENTITY_EXPORT BasePool
		{
		public:
			BasePool();
			virtual ~BasePool();

			virtual bool test(std::size_t) const = 0;
			virtual void destroy(std::size_t) = 0;
		};

		template <typename T>
		class ComponentPool final : public BasePool
		{
		public:
			ComponentPool() : BasePool()
			{
			}

			~ComponentPool()
			{
			}

			T& operator[](std::size_t x)
			{
				return this->pool[this->indices[x]];
			}

			bool test(std::size_t x) const override
			{
				return x < this->indices.size() && this->indices[x] != -1;
			}

			template <typename... Args>
			void construct(std::size_t x, Args&&... args)
			{
				if(x >= this->indices.size())
				{
					this->indices.resize(x + 1, -1);
				}

				this->pool.emplace_back(T{std::forward<Args>(args)...});
				this->indices[x] = static_cast<int>(this->pool.size());
			}

			void destroy(std::size_t x) override
			{
				// For a more efficient removal. Let's move the last element into place of the element
				// we are removing and then pop the last element off as it has been invalidated.
				auto tmp = std::move(this->pool.back());
				this->pool[this->indices[x]] = std::move(tmp);
				this->pool.pop_back();
				this->indices[x] = -1;
			}

		private:
			std::vector<T> pool{};
			std::vector<int> indices{};
		};
	}
}
