#include <age/core/Properties.h>

using namespace age::core;

Property::Property(std::string_view x) : name{x}
{
}

Property::~Property()
{
}

std::string Property::getName() const
{
	return this->name;
}

Properties::Properties()
{
}

Properties::Properties(const Properties&)
{
	// Do Nothing
}

Properties::Properties(Properties&&)
{
	// Do Nothing
}

Properties::~Properties()
{
}

Properties& Properties::operator=(const Properties&)
{
	// Do Nothing
	return *this;
}

Properties& Properties::operator=(Properties&&)
{
	// Do Nothing
	return *this;
}

Property* Properties::getProperty(std::string_view x)
{
	for(const auto& property : this->properties)
	{
		if(property->getName() == x)
		{
			return property.get();
		}
	}

	return nullptr;
}

const std::vector<std::unique_ptr<Property>>& Properties::getProperties() const
{
	return this->properties;
}
