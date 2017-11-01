#pragma once

#include <age/entity/ComponentPool.h>
#include <age/entity/Export.h>
#include <age/core/Object.h>
#include <bitset>

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT Entity
		{
		public:
			bool valid() const;

			template <typename T>
			void addComponent()
			{
				ComponentPool<T> pool{};

				if(T::index() >= manager->pools.size())
				{
					auto p = std::make_unique<ComponentPool<T>>();
					pool = p.get();
					manager->pools.push_back(std::move(p));
				}
				else
				{
					pool = static_cast<ComponentPool<T>*>(manager->pools[this->id].get());
				}

				if(this->id >= pool->size())
				{
					pool->resize(this->id + 1);
				}

				this->manager->componentMasks[this->id].set(T::index());
			}

			template <typename T>
			T& getComponent()
			{
				return static_cast<ComponentPool<T>*>(this->manager->pools[T::index()].get())->Components[this->id];
			}

			template <typename T>
			bool hasComponent()
			{
				return static_cast<ComponentPool<T>*>(this->manager->componentMasks[this->id].test(T::index()));
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

			const std::vector<Entity>& getEntities() const;

		private:
			friend class Entity;
			std::vector<Entity> entities;
			std::vector<std::unique_ptr<BasePool>> pools;
			std::vector<std::bitset<64>> componentMasks;
			std::vector<int> indexList;
		};
	}
}
