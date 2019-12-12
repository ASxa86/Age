#include <age/core/Reflection.h>
#include <algorithm>

using namespace age::core;

std::map<std::type_index, ReflType> Reflection::ReflMap;

ReflProp::ReflProp(const std::string& n) : Name{n}
{
}

ReflProp::~ReflProp()
{
}

ReflProp* ReflType::getProperty(std::string_view x) const
{
	const auto foundIt =
		std::find_if(std::begin(this->properties), std::end(this->properties), [x](const std::shared_ptr<ReflProp>& p) { return p->Name == x; });

	if(foundIt != std::end(this->properties))
	{
		return foundIt->get();
	}

	return nullptr;
}

std::vector<ReflProp*> ReflType::getProperties() const
{
	std::vector<ReflProp*> v;
	v.reserve(this->properties.size());

	std::transform(std::begin(this->properties), std::end(this->properties), std::back_inserter(v), [](const auto& x) { return x.get(); });

	return v;
}

const ReflType* const age::core::Reflection::Get(std::string_view x)
{
	for(const auto& [index, type] : ReflMap)
	{
		if(type.Name == x)
		{
			return &type;
		}
	}

	return nullptr;
}
