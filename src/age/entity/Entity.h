#pragma once

#include <age/entity/Export.h>

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT Entity
		{
		public:
			Entity();
			~Entity();

			size_t getID();

		private:
			size_t id;
		};
	}
}