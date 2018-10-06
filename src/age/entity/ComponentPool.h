#pragma once

#include <age/entity/Export.h>
#include <cstring>
#include <memory>
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
			ComponentPool(std::size_t x = 2048) : BasePool(), pool{(T*)std::malloc(x * sizeof(T))}, poolsize{x}
			{
				this->valid = new bool[this->poolsize];
				std::memset(this->valid, false, this->poolsize);
			}

			~ComponentPool()
			{
				for(auto i = 0; i < this->poolsize; ++i)
				{
					if(this->valid[i] == true)
					{
						this->destroy(i);
					}
				}

				delete[] this->valid;
				std::free(this->pool);
			}

			std::size_t capacity() const
			{
				return this->poolsize;
			}

			T& operator[](std::size_t x)
			{
				return this->pool[x];
			}

			bool test(std::size_t x) const override
			{
				return this->valid[x];
			}

			template <typename... Args>
			void construct(std::size_t x, Args&&... args)
			{
				new(this->pool + x) T{std::forward<Args>(args)...};
				this->valid[x] = true;
			}

			void destroy(std::size_t x) override
			{
				(this->pool + x)->~T();
				this->valid[x] = false;
			}

		private:
			///
			///	Using a deque in order for references to remain valid upon resizing.
			/// What would happen was when creating a new entity, the component pools would
			/// get resized which would invalidate previous references causing all kinds of
			/// undefined behaviours.
			///
			T* pool{};
			bool* valid{};
			std::size_t poolsize;
		};
	}
}
