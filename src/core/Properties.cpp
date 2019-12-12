#include <age/core/Properties.h>

using namespace age::core;

Property::Property(std::string_view x) : name{x}
{
}

Property::~Property()
{
}

const std::string& Property::getName() const
{
	return this->name;
}

Properties::Properties()
{
}

Properties::Properties(const Properties&)
{
	// Do Nothing
	// Each derived type will have registered its own member variables.
}

Properties::Properties(Properties&&)
{
	// Do Nothing
	// Each derived type will have registered its own member variables.
}

Properties::~Properties()
{
}

Properties& Properties::operator=(const Properties&)
{
	// Do Nothing
	// Each derived type will have registered its own member variables.
	return *this;
}

Properties& Properties::operator=(Properties&&)
{
	// Do Nothing
	// Each derived type will have registered its own member variables.
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
