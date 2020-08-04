#include <azule/reflection/Property.h>

using namespace azule;

Property::Property(std::string_view x) : name{x}
{
}

Property::~Property()
{
}

std::string_view Property::getName() const noexcept
{
	return this->name;
}
