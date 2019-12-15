#pragma once

#include <age/core/EventQueue.h>
#include <age/core/Object.h>
#include <age/entity/ComponentPool.h>
#include <age/entity/export.h>
#include <deque>
#include <map>
#include <tuple>
#include <typeindex>

namespace age
{
	namespace entity
	{
		class Entity;
		///
		///	\class EntityManager
		///
		///	\brief This class manages all entities for a given instance.
		///
		///	This class is what makes Entities possible in an Entity Component System.
		///	The complexity of this class falls under keeping entities allocated to an object along with their components.
		///	By using sequential memory for the object pool, processing large numbers of entities becomes easy for a cpu to handle.
		///
		///	\author Aaron Shelley
		///
		///	\date April 14, 2018
		///
		class AGE_ENTITY_EXPORT EntityManager : public age::core::Object
		{
		public:
			///
			///	For increased performance the entity manager provides creation and destruction of entities
			/// within a fixed pool.
			///
			///	\param reserve Reserve a number of entities before allocations need to be resized.
			///
			EntityManager(std::size_t reserve = 1024);
			~EntityManager() override;

			///
			///	Return a free entity in the object pool.
			///	If there are no more free entities left in the object pool, than the object pool will be expanded.
			///
			Entity create();

			///
			///	Free up an entity in the object pool.
			///
			void destroy(Entity x);

			///
			///	Return if the entity is a valid entity that holds a spot within an object pool.
			///	The entity is invalid if it has been destroyed.
			///
			bool valid(Entity x) const;

			///
			///	Get a read-only list of all entities within the entity manager.
			///	This list contains all allocated entities, valid or not.
			///
			const std::vector<Entity>& getEntities() const;

			template <typename T>
			struct identity
			{
				typedef T type;
			};

			///
			///	Loop through each entity that contains the given components and invoke the given function on them.
			///
			///	This function will efficiently call the given function on only the entities with the given components.
			///
			template <typename... Args>
			void each(typename identity<std::function<void(Entity&, Args&...)>>::type x);

			template <typename T>
			ComponentPool<T>* getPool()
			{
				auto pool = static_cast<ComponentPool<T>*>(this->pools[typeid(T)].get());

				if(pool == nullptr)
				{
					auto p = std::make_unique<ComponentPool<T>>(this->reserve);
					pool = p.get();
					this->pools[typeid(T)] = std::move(p);
				}

				return pool;
			}

			const std::map<std::type_index, std::unique_ptr<BasePool>>& getPools() const;

		private:
			std::map<std::type_index, std::unique_ptr<BasePool>> pools;
			std::vector<Entity> entities;
			std::vector<Entity> destroyed;
			std::size_t reserve;
		};
	}
}

#include <age/entity/Entity.h>

template <typename... Args>
void age::entity::EntityManager::each(typename age::entity::EntityManager::identity<std::function<void(age::entity::Entity&, Args&...)>>::type x)
{
	const auto tuple = std::make_tuple(this->template getPool<Args>()...);

	std::apply(
		[this, &x](auto... pool) {
			for(auto& e : this->entities)
			{
				const auto valid = e.id != -1 && ((pool->test(e.id)) && ...);

				if(valid == true)
				{
					x(e, (*pool)[e.id]...);
				}
			}
		},
		tuple);
}
