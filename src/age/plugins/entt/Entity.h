#pragma once

#include <age/entity/Entity.h>
#include <age/plugins/entt/Export.h>

#pragma warning(push, 0)
#include <entt/entt.hpp>
#pragma warning(pop)

namespace age
{
	namespace entt
	{
		class AGE_ENTT_EXPORT Entity : public age::entity::Entity
		{
		public:
			Entity();

			::entt::registry::entity_type entity_type;
		};
	}
}