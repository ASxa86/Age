#pragma once

#include <azule/reflection/Property.h>
#include <azule/utilities/String.h>
#include <functional>

namespace azule
{
	///
	///	\class TemplateMethod
	///
	///	\brief This class manages ReflProp for member functions.
	///
	///	\author Aaron Shelley
	///
	///	\date February 17, 2020
	///
	//template <typename Writer, typename Reader>
	template <typename T>
	class PropertyTemplateMethod : public Property
	{
	public:
		// using Type = typename azule::function_t<&Writer::operator()>::arg_type;
		//using T = typename azule::functor_t<Writer>::arg_type;
		using Writer = std::function<void(T)>;
		using Reader = std::function<T()>;

		PropertyTemplateMethod(std::string_view n, Writer w, Reader r) : Property{n}, writer{std::move(w)}, reader{std::move(r)}
		{
		}

		void setValue(std::any value) override
		{
			this->writer(std::any_cast<T>(value));
		}

		std::any getValue() const override
		{
			return this->reader();
		}

		void setValueString(std::string_view x) override
		{
			this->writer(azule::StringTo<T>(x));
		}

		std::string getValueString() const override
		{
			return azule::ToString(this->reader());
		}

		const std::type_info& getTypeInfo() const noexcept override
		{
			return typeid(T);
		}

	private:
		Writer writer;
		Reader reader;
	};
}
