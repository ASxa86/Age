#pragma once

#include <age/entity/Export.h>
#include <vector>

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT BasePool
		{
		public:
			BasePool();
			virtual ~BasePool();

			virtual void resize(std::size_t x) = 0;
			virtual std::size_t size() const = 0;

			void setValid(std::size_t x, bool v = true);
			bool getValid(std::size_t x) const;

		protected:
			std::vector<bool> valid;
		};

		template <typename T>
		class ComponentPool : public BasePool
		{
		public:
			void resize(std::size_t x) override
			{
				this->components.resize(x);
				this->valid.resize(x);
			}

			std::size_t size() const
			{
				return this->components.size();
			}

			T& get(std::size_t x)
			{
				return this->components[x];
			}

		private:
			std::vector<T> components;
		};
	}
}
