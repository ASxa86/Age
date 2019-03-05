#pragma once

#include <age/core/Pimpl.h>
#include <age/entity/Entity.h>
#include <functional>
#include <string>
#include <vector>

namespace age
{
	class ComponentFactory
	{
	public:
		static ComponentFactory& Instance();

		void addComponent(age::entity::Entity& e, const std::string& x);
		void removeComponent(age::entity::Entity& e, const std::string& x);
		std::vector<std::string> getComponentList() const;

		template <typename T>
		void registerComponent()
		{
			this->registerAdd(typeid(T).name(), [](age::entity::Entity& e) { e.addComponent<T>(); });
			// this->registerRemove(typeid(T).name(), [](age::entity::Entity& e) { e.removeComponent<T>(); });
		}

	private:
		ComponentFactory() = default;

		void registerAdd(const std::string& x, const std::function<void(age::entity::Entity&)>& f);
		void registerRemove(const std::string& x, const std::function<void(age::entity::Entity&)>& f);

		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
