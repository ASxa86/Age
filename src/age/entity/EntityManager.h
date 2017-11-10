#pragma once

#include <age/entity/Component.h>
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
			int getID() const;
			bool valid() const;
			void destroy() const;


			template <typename T, typename... Args>
			void addComponent(Args&& ...args)
			{
				ComponentPool<T>* pool{};

				if(Component<T>::index() >= this->manager->pools.size())
				{
					auto p = std::make_unique<ComponentPool<T>>();
					pool = p.get();
					this->manager->pools.push_back(std::move(p));
				}
				else
				{
					pool = static_cast<ComponentPool<T>*>(this->manager->pools[Component<T>::index()].get());
				}

				if(this->id >= pool->size())
				{
					pool->resize(this->id + 1);
				}

				pool->Components[this->id] = T(std::forward<Args>(args)...);
				this->manager->componentMasks[this->id].set(Component<T>::index());
			}

			template <typename T>
			void removeComponent()
			{
				if(Component<T>::index() < this->manager->pools.size())
				{
					this->manager->componentMasks[this->id].reset(Component<T>::index());
				}
			}

			template <typename T>
			T& getComponent()
			{
				return static_cast<ComponentPool<T>*>(this->manager->pools[Component<T>::index()].get())->Components[this->id];
			}

			template <typename T>
			bool hasComponent()
			{
				return this->manager->componentMasks[this->id].test(Component<T>::index());
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

		private:
			friend class Entity;
			std::vector<Entity> entities;
			std::vector<std::unique_ptr<BasePool>> pools;
			std::vector<std::bitset<64>> componentMasks;
			std::vector<bool> validEntities;
			std::vector<int> indexList;
		};
	}
}
