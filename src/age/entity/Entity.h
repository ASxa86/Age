#pragma once

#include <age/core/EventQueue.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/Export.h>
#include <typeindex>

namespace age
{
	namespace entity
	{
		class Component;
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
			Entity();

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
			///	Operator overload for comparing two entity ids as equal.
			///
			bool operator==(const Entity& e) const;

			///
			///	Operator overload for comparing two entity ids as not equal.
			///
			bool operator!=(const Entity& e) const;

			///
			///	Add a component to the entity and returns it.
			///	This will simply return the component if it already exists.
			///
			template <typename T, typename... Args>
			T& addComponent(Args&&... args);

			template <typename T>
			void addComponent(const T& component);

			///
			///	Remove a component to the entity.
			///
			template <typename T>
			void removeComponent();

			///
			///	Get a component to the entity.
			///
			template <typename T>
			T& getComponent() const;

			///
			///	Get a list of type info of all components that exist on the entity.
			///
			std::vector<Component*> getComponents() const;

			///
			///	Check if this entity has a component.
			///
			template <typename T>
			bool hasComponent() const;

		private:
			friend class EntityManager;

			int id;
			EntityManager* manager;
		};
	}
}

#include <age/entity/EntityManager.h>

template <typename T, typename... Args>
T& age::entity::Entity::addComponent(Args&&... args)
{
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component.");

	const auto pool = this->manager->template getPool<T>();

	if(pool->test(this->id) == false)
	{
		pool->construct(this->id, std::forward<Args>(args)...);

		auto event = std::make_unique<EntityEvent>(*this, EntityEvent::Type::ComponentAdded);
		event->Component = &(*pool)[this->id];
		age::core::EventQueue::Instance().sendEvent(std::move(event));
	}

	return (*pool)[this->id];
}

template <typename T>
void age::entity::Entity::addComponent(const T& x)
{
	const auto pool = this->manager->template getPool<T>();

	if(pool->test(this->id) == false)
	{
		pool->construct(this->id);

		auto event = std::make_unique<EntityEvent>(*this, EntityEvent::Type::ComponentAdded);

		auto& component = (*pool)[this->id];
		component = x;
		event->setComponent(&component);
		age::core::EventQueue::Instance().sendEvent(std::move(event));
	}
}

template <typename T>
void age::entity::Entity::removeComponent()
{
	const auto pool = this->manager->template getPool<T>();

	if(pool->test(this->id) == true)
	{
		auto event = std::make_unique<EntityEvent>(*this, EntityEvent::Type::ComponentRemoved);
		event->Component = &(*pool)[this->id];
		age::core::EventQueue::Instance().sendEvent(std::move(event));
		pool->destroy(this->id);
	}
}

template <typename T>
T& age::entity::Entity::getComponent() const
{
	const auto pool = this->manager->template getPool<T>();
	return (*pool)[this->id];
}

template <typename T>
bool age::entity::Entity::hasComponent() const
{
	const auto pool = this->manager->template getPool<T>();
	return pool->test(this->id);
}
