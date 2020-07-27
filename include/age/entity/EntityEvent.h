#pragma once

#include <age/core/Event.h>
#include <age/utilities/Pimpl.h>
#include <age/entity/export.h>
#include <any>
#include <typeindex>

namespace age
{
	namespace entity
	{
		class Entity;
		class Component;

		///
		///	\class EntityEvent
		///
		///	\brief An event that notifies any entity or componenet additions or removals.
		///
		///	\date Decemeber 5, 2017
		///
		///	\author Aaron Shelley
		///
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

			EntityEvent(Entity* e, Type t);
			~EntityEvent() override;

			Entity* getEntity() const;
			EntityEvent::Type getType() const;

			age::entity::Component* Component{};

		private:
			Entity* entity;
			Type type;
		};
	}
}
