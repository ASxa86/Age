#pragma once

#include <azule/World.h>
#include <azule/export.hxx>
#include <entt/entt.hpp>

namespace azule
{
	class AZULE_EXPORT Entity
	{
	public:
		Entity(entt::entity handle, World* world);

		template <typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			return this->world->registry.emplace<T>(this->handle, std::forward<Args>(args)...);
		}

		template <typename T>
		T& getComponent()
		{
			return this->world->registry.get<T>(this->handle);
		}

		template <typename T>
		bool hasComponent()
		{
			return this->world->registry.has<T>(this->handle);
		}

		template <typename T>
		void removeComponent()
		{
			this->world->registry.remove<T>(this->handle);
		}

	private:
		entt::entity handle{entt::null};
		World* world{nullptr};
	};
}