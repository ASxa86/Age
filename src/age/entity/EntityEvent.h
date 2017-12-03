#pragma once

#include <age/core/Pimpl.h>
#include <age/core/Event.h>
#include <age/entity/Export.h>

namespace age
{
	namespace entity
	{
		class Entity;

		class AGE_ENTITY_EXPORT EntityEvent : public age::core::Event
		{
		public:
			enum class Type : uint8_t
			{
				EntityAdded,
				EntityRemoved,
				ComponentAdded,
				ComponentRemoved
			};

			EntityEvent::EntityEvent(Entity e, Type t);
			EntityEvent::~EntityEvent();

			Entity EntityEvent::getEntity() const;
			EntityEvent::Type EntityEvent::getType() const;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
