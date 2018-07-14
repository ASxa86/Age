#pragma once

#include <age/entity/Export.h>
#include <deque>
#include <optional>

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

			virtual std::size_t size() const = 0;
			virtual void allocate() = 0;

			void setValid(std::size_t x, bool v = true);
			bool getValid(std::size_t x) const;

		protected:
			std::deque<bool> valid;
		};

		template <typename T>
		class ComponentPool : public BasePool
		{
		public:
			ComponentPool(std::size_t x) : BasePool()
			{
				for(std::size_t i = 0; i < x; ++i)
				{
					this->allocate();
				}
			}

			std::size_t size() const
			{
				return this->components.size();
			}

			T& get(std::size_t x)
			{
				return this->components[x];
			}

			///
			///	Allocate a new chunk of memory for components.
			///
			void allocate() override
			{
				// Simply let the stl container handle allocating extra memory
				// when necessary.
				this->components.push_back({});
				this->valid.push_back({});
			}

		private:
			///
			///	Using a deque in order for references to remain valid upon resizing.
			/// What would happen was when creating a new entity, the component pools would
			/// get resized which would invalidate previous references causing all kinds of
			/// undefined behaviours.
			///
			std::deque<T> components;
		};
	}
}
