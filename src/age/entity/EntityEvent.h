#pragma once

#include <age/core/Event.h>
#include <age/core/Pimpl.h>
#include <age/entity/Export.h>
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

			EntityEvent(const Entity& e, Type t);
			~EntityEvent() override;

			const Entity& getEntity() const;
			EntityEvent::Type getType() const;

			Component* Component{};

		private:
			const Entity& entity;
			Type type;
		};
	}
}
