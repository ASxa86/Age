#pragma once

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <rttr/registration.h>

#ifdef WIN32
#pragma warning(pop)
#endif

#include <age/entity/Entity.h>
#include <typeindex>

namespace age
{
	class Property
	{
	public:
		Property(age::entity::Entity& x);

		static std::unordered_map<std::type_index, std::string> Alias;

		void addComponent(const std::string& component);
		void removeComponent(const std::string& component);

		void setValue(const std::string& name, const std::string& property, rttr::argument arg);
		void setValue(const std::type_index& type, const std::string& property, rttr::argument arg);

		std::string getValue(const std::string& name, const std::string& property);
		std::string getValue(const std::type_index& type, const std::string& property);

	private:
		age::entity::Entity& entity;
		std::unordered_map<std::string, rttr::variant> components;
	};
}
