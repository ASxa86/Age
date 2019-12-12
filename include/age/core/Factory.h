#pragma once

#include <age/core/Export.h>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <typeindex>
#include <vector>

namespace boost
{
	namespace dll
	{
		class shared_library;
	}
}

namespace age
{
	namespace core
	{
		class Object;

		struct AGE_CORE_EXPORT CreatorBase
		{
			virtual ~CreatorBase();
			virtual std::unique_ptr<Object> create() const;
		};

		template <typename T>
		struct Creator : public CreatorBase
		{
			std::unique_ptr<Object> create() const override
			{
				static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");
				return std::make_unique<T>();
			}
		};

		class AGE_CORE_EXPORT Factory
		{
		public:
			struct AGE_CORE_EXPORT Type
			{
				Type(const std::type_index& type = typeid(Type));

				std::set<std::type_index> BaseTypes;
				std::set<std::string> Aliases;
				std::string Name;
				std::string NameClean;
				std::type_index TypeIndex;
				std::shared_ptr<CreatorBase> Creator;

				template <typename T>
				Type& addBaseType()
				{
					this->BaseTypes.insert(typeid(T));
					return *this;
				}

				Type& addAlias(std::string_view x);

				bool valid() const;
				bool operator==(std::string_view x) const;
				bool operator!=(std::string_view x) const;
				bool operator==(const Type& x) const;
				bool operator!=(const Type& x) const;
			};

			Factory(const Factory&) = delete;
			~Factory();

			Factory& operator=(const Factory&) = delete;
			static Factory& Instance();

			Factory::Type getType(std::string_view x);
			Factory::Type getType(std::type_index x);
			std::vector<Factory::Type> getTypes() const;
			std::vector<Factory::Type> getTypesFromBase(std::type_index x);
			std::unique_ptr<Object> create(std::string_view x);
			std::unique_ptr<Object> create(std::type_index x);

			template <typename T>
			std::unique_ptr<T> create(std::string_view x)
			{
				auto type = this->getType(x);

				if(type.valid() == true)
				{
					auto object = type.Creator->create();
					auto p = dynamic_cast<T*>(object.get());

					if(p != nullptr)
					{
						// Release ownership so that we may return an owning pointer to the given type.
						object.release();
						return std::unique_ptr<T>(p);
					}
				}

				return {};
			}

			template <typename T>
			Factory::Type& registerType(std::string_view x)
			{
				Factory::Type type(typeid(T));
				type.Name = x;
				type.NameClean = x.substr(x.find_last_of(":") + 1);
				type.Creator = std::make_shared<Creator<T>>();
				this->types.emplace_back(std::move(type));
				return this->types.back();
			}

		private:
			Factory();

			std::vector<Factory::Type> types;
			std::vector<boost::dll::shared_library> loadedLibraries;
			bool initialized{false};
		};
	}
}

#define AgeFactoryRegister(T) age::core::Factory::Instance().registerType<T>(#T)
