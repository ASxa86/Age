#pragma once

#include <age/core/Export.h>
#include <age/core/Pimpl.h>
#include <string>

namespace age
{
	namespace core
	{
		class Object;

		struct AGE_CORE_EXPORT CreatorBase
		{
			virtual ~CreatorBase();
			virtual std::shared_ptr<Object> create() const;
		};

		template <typename T>
		struct Creator : public CreatorBase
		{
			std::shared_ptr<Object> create() const override
			{
				static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");
				return std::make_shared<T>();
			}
		};

		class AGE_CORE_EXPORT Factory
		{
		public:
			Factory(const Factory&) = delete;
			~Factory();

			Factory& operator=(const Factory&) = delete;
			static Factory& Instance();

			///
			///	\brief Create type given typeid string.
			///
			std::shared_ptr<Object> create(const std::string& x) const;

			template <typename T>
			std::shared_ptr<T> create(const std::string& x) const
			{
				auto object = this->create(x);
				return std::dynamic_pointer_cast<T>(object);
			}

			void registerType(const std::string& id, std::shared_ptr<CreatorBase> creator);

			template <typename T>
			static void RegisterType(const std::string& id = std::string())
			{
				auto x = id;

				if(x.empty() == true)
				{
					x = typeid(T).name();
				}

				Factory::Instance().registerType(x, std::make_shared<Creator<T>>());
			}

		private:
			Factory();

			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
