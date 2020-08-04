#pragma once

#include <azule/utilities/String.h>
#include <azule/reflection/Property.h>
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
	template <typename Arg, typename Return>
	class PropertyTemplateMethod : public Property
	{
	public:
		PropertyTemplateMethod(std::string_view n, std::function<void(Arg)> w, std::function<Return()> r)
			: Property{n}, writer{std::move(w)}, reader{std::move(r)}
		{
		}

		void setValue(std::any value) override
		{
			this->writer(std::any_cast<Arg>(value));
		}

		std::any getValue(std::any x) const override
		{
			return this->reader();
		}

		virtual void setValueString(std::string_view x) override
		{
			this->writer(azule::StringTo<Arg>(x));
		}

		virtual std::string getValueString() const override
		{
			return azule::ToString(this->reader());
		}

		virtual const std::type_info& getTypeInfo() const noexcept override
		{
			return typeid(Arg);
		}

	private:
		std::function<void(Arg)> writer;
		std::function<Return()> reader;
	};
}
