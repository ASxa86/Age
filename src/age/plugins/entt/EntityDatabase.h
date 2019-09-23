#pragma once

#include <age/entity/EntityDatabase.h>
#include <age/plugins/entt/Export.h>

namespace age
{
	namespace entt
	{
		class AGE_ENTT_EXPORT EntityDatabase : public age::entity::EntityDatabase
		{
		public:
			EntityDatabase();
		};
	}
}