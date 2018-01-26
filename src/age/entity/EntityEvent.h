#pragma once

#include <age/core/Pimpl.h>
#include <age/core/Event.h>
#include <age/entity/Export.h>
#include <any>

namespace age
{
	namespace entity
	{
		class Entity;

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

			EntityEvent(Entity e, Type t);
			~EntityEvent() override;

			Entity getEntity() const;
			EntityEvent::Type getType() const;

			template <typename T>
			void setComponent(T* x)
			{
				this->component = x;
			}

			template <typename T>
			T* getComponent() const
			{
				T* c{};

				try
				{
					c = std::any_cast<T*>(this->component);
				}
				catch(...)
				{
				}

				return c;
			}

		private:
			std::any component;

			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
