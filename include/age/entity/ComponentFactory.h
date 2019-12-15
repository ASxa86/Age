#pragma once

#include <age/entity/Entity.h>
#include <age/entity/export.h>
#include <boost/dll/import.hpp>
#include <map>
#include <string>

namespace age
{
	namespace entity
	{
		class Component;

		struct AGE_ENTITY_EXPORT ComponentCreatorBase
		{
			virtual ~ComponentCreatorBase();
			virtual Component* add(Entity x) const = 0;
			virtual void remove(Entity x) const = 0;
		};

		template <typename T>
		struct ComponentCreator : public ComponentCreatorBase
		{
			Component* add(Entity x) const override
			{
				static_assert(std::is_base_of<Component, T>::value, "T must derive from Object");
				return &x.addComponent<T>();
			}

			void remove(Entity x) const override
			{
				x.removeComponent<T>();
			}
		};

		class AGE_ENTITY_EXPORT ComponentFactory
		{
		public:
			ComponentFactory(const ComponentFactory&) = delete;
			ComponentFactory& operator=(const ComponentFactory&) = delete;
			ComponentFactory(ComponentFactory&&) = delete;
			ComponentFactory& operator=(ComponentFactory&&) = delete;

			static ComponentFactory& Instance();

			///
			///	\brief Create type given typeid string.
			///
			Component* add(Entity x, std::string component) const;
			void remove(Entity x, std::string component) const;
			std::string alias(const std::type_index& x);

			template <typename T>
			static void RegisterType(std::string x)
			{
				ComponentFactory::Instance().typeAlias[typeid(T)] = x;
				ComponentFactory::Instance().FactoryMap[x] = std::make_unique<ComponentCreator<T>>();
			}

			std::map<std::string, std::unique_ptr<ComponentCreatorBase>> FactoryMap;

		private:
			ComponentFactory();

			std::map<std::type_index, std::string> typeAlias;
			std::vector<boost::dll::shared_library> loadedLibraries;
			bool initialized{false};
		};
	}
}
