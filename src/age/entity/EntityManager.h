#pragma once

#include <age/core/Object.h>
#include <age/entity/Component.h>
#include <age/entity/ComponentPool.h>
#include <age/entity/Export.h>
#include <map>
#include <tuple>
#include <typeindex>

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT Entity
		{
		public:
			int getID() const;
			bool valid() const;
			void destroy() const;

			template <typename T, typename... Args>
			T& addComponent(Args&&... args)
			{
				const auto pool = this->manager->getPool<T>();

				if(this->id >= pool->size())
				{
					pool->resize(this->id + 1);
				}

				pool->get(this->id) = T(std::forward<Args>(args)...);
				pool->setValid(this->id);
				return pool->get(this->id);
			}

			template <typename T>
			void removeComponent()
			{
				const auto pool = this->manager->getPool<T>();
				pool->setValid(this->id, false);
			}

			template <typename T>
			T& getComponent()
			{
				const auto pool = this->manager->getPool<T>();
				return pool->get(this->id);
			}

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

		class AGE_ENTITY_EXPORT EntityManager : public age::core::Object
		{
		public:
			EntityManager();
			~EntityManager() override;

			Entity create();
			void destroy(Entity x);
			bool valid(Entity x) const;

			const std::vector<Entity>& getEntities() const;

			template <typename T> struct identity { typedef T type; };

			template <typename... Args>
			void each(typename identity<std::function<void(Entity, Args&...)>>::type x)
			{
				const auto tuple = std::make_tuple(this->getPool<Args>()...);

				std::apply(
					[this, &x](auto... pool) {
						for(auto e : this->entities)
						{
							const auto validList = {true, (pool != nullptr && pool->getValid(e.id))...};
							const auto valid = std::all_of(std::begin(validList), std::end(validList), [](auto x) { return x; });

							if(valid == true)
							{
								x(e, pool->get(e.id)...);
							}
						}
					},
					tuple);
			}

			template <typename T>
			ComponentPool<T>* getPool()
			{
				auto pool = static_cast<ComponentPool<T>*>(this->pools[typeid(T)].get());

				if(pool == nullptr)
				{
					auto p = std::make_unique<ComponentPool<T>>();
					p->resize(this->entities.size());
					pool = p.get();
					this->pools[typeid(T)] = std::move(p);
				}

				return pool;
			}

		private:
			friend class Entity;
			std::map<std::type_index, std::unique_ptr<BasePool>> pools;
			std::vector<Entity> entities;
			std::vector<bool> validEntities;
			std::vector<int> indexList;
		};
	}
}
