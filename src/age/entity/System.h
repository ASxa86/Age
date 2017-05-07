#pragma once

#include <age/entity/Export.h>

namespace age
{
	namespace entity
	{
		///
		///	\class System
		///
		///	\brief The system in Entity Component System, this class is in charge of managing entity components and updating them.
		///
		class AGE_ENTITY_EXPORT System
		{
		public:
			System();
			virtual ~System();
		};
	}
}
