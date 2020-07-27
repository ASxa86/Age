#pragma once

#include <azule/core/Event.h>
#include <azule/utilities/Pimpl.h>
#include <azule/entity/export.h>
#include <any>
#include <typeindex>

namespace azule
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
		class AZULE_ENTITY_EXPORT EntityEvent : public azule::core::Event
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

			azule::entity::Component* Component{};

		private:
			Entity* entity;
			Type type;
		};
	}
}
