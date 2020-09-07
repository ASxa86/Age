#pragma once

#include <azule/reflection/Property.h>
#include <azule/utilities/String.h>

namespace azule
{
	///
	///	\class TemplateProperty
	///
	///	\brief This class manages ReflProp for public class member variables.
	///
	///	\author Aaron Shelley
	///
	///	\date February 17, 2020
	///
	template <typename T>
	class PropertyTemplateMember : public Property
	{
	public:
		PropertyTemplateMember(std::string_view n, T& p) : Property{n}, property{p}
		{
		}

		void setValue(std::any value) override
		{
			this->property = std::any_cast<T>(value);
		}

		std::any getValue() const override
		{
			return this->property;
		}

		virtual void setValueString(std::string_view x) override
		{
			azule::StringTo<T>(x, this->property);
		}

		virtual std::string getValueString() const override
		{
			return azule::ToString(this->property);
		}

		virtual const std::type_info& getTypeInfo() const noexcept override
		{
			return typeid(T);
		}

		void serialize(boost::archive::polymorphic_iarchive& ar, unsigned int version) override
		{
			ar& boost::make_nvp(this->getName().data(), this->property);
		}

		void serialize(boost::archive::polymorphic_oarchive& ar, unsigned int version) const override
		{
			ar& boost::make_nvp(this->getName().data(), this->property);
		}

	private:
		T& property;
	};
}
