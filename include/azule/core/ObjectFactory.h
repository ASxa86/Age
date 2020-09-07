#pragma once

#include <azule/core/Object.h>
#include <azule/utilities/TypeName.h>
#include <map>
#include <typeindex>

namespace azule
{
	namespace impl
	{
		class CreatorBase
		{
		public:
			virtual std::shared_ptr<Object> create() const = 0;
		};

		template <typename T>
		class Creator : public CreatorBase
		{
			std::shared_ptr<Object> create() const override
			{
				return std::make_shared<T>();
			}
		};

		class Type
		{
		public:
			Type(const std::type_info& t, std::string_view n) : typeID{t}, name{n}
			{
			}

			std::unique_ptr<CreatorBase> creator;
			const std::type_info& typeID;
			std::string name;
			std::string alias;
		};
	}

	class AZULE_EXPORT ObjectFactory
	{
	public:
		ObjectFactory() = default;
		ObjectFactory(const ObjectFactory&) = delete;
		ObjectFactory(ObjectFactory&& x) noexcept = delete;
		ObjectFactory& operator=(const ObjectFactory&) = delete;
		ObjectFactory& operator=(ObjectFactory&&) noexcept = delete;

		template <typename T>
		void registerType(std::string_view alias = {})
		{
			static_assert(std::is_base_of<Object, T>::value == true, "T must derive from cormyr::Object.");

			auto type = std::make_unique<impl::Type>(typeid(T), TypeName<T>());
			type->creator = std::make_unique<impl::Creator<T>>();
			type->alias = alias;
			this->types.push_back(std::move(type));
		}

		std::shared_ptr<Object> create(std::string_view x) const;
		std::shared_ptr<Object> create(const std::type_info& x) const;

		template <typename T>
		std::shared_ptr<T> create(std::string_view x) const
		{
			return std::dynamic_pointer_cast<T>(this->create(x));
		}

	private:
		std::vector<std::unique_ptr<impl::Type>> types;
	};
}
