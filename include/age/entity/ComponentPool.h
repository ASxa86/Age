#pragma once

#include <age/entity/Export.h>
#include <bitset>
#include <vector>

namespace age
{
	namespace entity
	{
		class Component;

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

			virtual Component* component(std::size_t) = 0;
			virtual bool test(std::size_t) const = 0;
			virtual void destroy(std::size_t) = 0;
		};

		template <typename T>
		class ComponentPool final : public BasePool
		{
		public:
			ComponentPool(std::size_t reserve = 1024) : BasePool(), pool(), indices()
			{
				this->pool.reserve(reserve);
				this->indices.reserve(reserve);
			}

			~ComponentPool()
			{
			}

			T& operator[](std::size_t x)
			{
				return this->pool[this->indices[x]];
			}

			Component* component([[maybe_unused]] std::size_t x)
			{
				if constexpr(std::is_base_of<Component, T>::value == true)
				{
					return &this->pool[this->indices[x]];
				}
				else
				{
					return nullptr;
				}
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

				this->pool.emplace_back(std::forward<Args>(args)...);
				this->indices[x] = static_cast<int>(this->pool.size()) - 1;
				this->direct.push_back(static_cast<int>(x));
			}

			void destroy(std::size_t x) override
			{
				// For a more efficient removal. Let's move the last element into place of the element
				// we are removing and then pop the last element off as it has been invalidated.
				auto tmp = std::move(this->pool.back());
				this->pool[this->indices[x]] = std::move(tmp);
				this->pool.pop_back();

				const auto back = this->direct.back();
				auto& candidate = this->indices[x];
				this->indices[back] = candidate;
				this->direct[candidate] = back;
				candidate = -1;
				this->direct.pop_back();
			}

		private:
			std::vector<T> pool;
			std::vector<int> indices;
			std::vector<int> direct;
		};
	}
}
