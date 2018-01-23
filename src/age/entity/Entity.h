#pragma once

#include <age/core/EventQueue.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/Export.h>

namespace age
{
	namespace entity
	{
		class EntityManager;

		///
		///	\class Entity
		///
		///	\brief This class is an id container that represents a game object.
		///
		///	This is the Entity in the Entity Component System design pattern. Use this class
		///	to define the behaviour of a game object by adding multiple components to it.
		///
		///	\date December 3, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_ENTITY_EXPORT Entity
		{
		public:
			///
			///	Get the ID of this entity.
			///
			///	The id represents the index of the entity within an array.
			///
			int getID() const;

			///
			///	Returns if this entity is valid.
			///
			///	An entity is valid when created and invalid when destroyed.
			///
			bool valid() const;

			///
			///	Mark this entity as destroyed within the entity manager.
			///	This will invalidate the entity.
			///
			void destroy() const;

			///
			///	Operator overload for compairing two entity ids against each other.
			///
			bool operator==(const Entity& e) const;

			///
			///	Add a component to the entity.
			///
			template <typename T, typename... Args>
			T& addComponent(Args&&... args)
			{
				const auto pool = this->manager->getPool<T>();

				if(pool->getValid(this->id) == false)
				{
					if(this->id >= pool->size())
					{
						pool->resize(this->id + 1);
					}

					pool->get(this->id) = T(std::forward<Args>(args)...);
					pool->setValid(this->id);

					auto event = std::make_unique<EntityEvent>(*this, EntityEvent::Type::ComponentAdded);
					event->setComponent(&pool->get(this->id));
					age::core::EventQueue::Instance().sendEvent(std::move(event));
				}

				return pool->get(this->id);
			}

			///
			///	Remove a component to the entity.
			///
			template <typename T>
			void removeComponent()
			{
				const auto pool = this->manager->getPool<T>();

				if(pool->getValid(this->id) == true)
				{
					pool->setValid(this->id, false);
					auto event = std::make_unique<EntityEvent>(*this, EntityEvent::Type::ComponentRemoved);
					event->setComponent(&pool->get(this->id));
					age::core::EventQueue::Instance().sendEvent(std::move(event));
				}
			}

			///
			///	Get a component to the entity.
			///
			template <typename T>
			T& getComponent()
			{
				const auto pool = this->manager->getPool<T>();
				return pool->get(this->id);
			}

			///
			///	Check if this entity has a component.
			///
			template <typename T>
			bool hasComponent()
			{
				const auto pool = this->manager->getPool<T>();
				return pool->getValid(this->id);
			}

		private:
			friend class EntityManager;
			Entity();

			int id;
			EntityManager* manager;
		};
	}
}
