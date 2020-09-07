#include <azule/reflection/Properties.h>
#include <algorithm>

using namespace azule;

Property* Properties::getProperty(std::string_view name) const noexcept
{
	const auto foundIt = std::find_if(std::begin(this->properties), std::end(this->properties), [name](auto& p) { return p->getName() == name; });

	if(foundIt != std::end(this->properties))
	{
		return foundIt->get();
	}

	return nullptr;
}

const std::vector<std::unique_ptr<Property>>& Properties::getProperties() const noexcept
{
	return this->properties;
}

void Properties::serialize(boost::archive::polymorphic_iarchive& ar, unsigned int version)
{
	for(auto& property : this->properties)
	{
		ar&* property;
	}
}

void Properties::serialize(boost::archive::polymorphic_oarchive& ar, unsigned int version) const
{
	for(auto& property : this->properties)
	{
		ar&* property;
	}
}
