#include <age/utilities/Reflection.h>
#include <algorithm>

using namespace age::utilities;

std::map<std::type_index, ReflType> Reflection::ReflMap;

ReflProp::ReflProp(const std::string& n) : Name{n}
{
}

ReflProp::~ReflProp()
{
}

ReflType::ReflType() : baseTypeIt{std::end(Reflection::ReflMap)}, index{typeid(ReflType)}
{
}

ReflType::ReflType(const std::string& n, const std::type_info& x) : Name{n}, baseTypeIt{std::end(Reflection::ReflMap)}, index{typeid(ReflType)}
{
}

ReflProp* ReflType::getProperty(std::string_view x) const
{
	const auto properties = this->getProperties();
	const auto foundIt = std::find_if(std::begin(properties), std::end(properties), [x](ReflProp* p) { return p->Name == x; });

	if(foundIt != std::end(properties))
	{
		return *foundIt;
	}

	return nullptr;
}

std::vector<ReflProp*> ReflType::getProperties() const
{
	std::vector<ReflProp*> v;

	if(this->baseTypeIt != std::cend(Reflection::ReflMap))
	{
		auto props = this->baseTypeIt->second.getProperties();
		v.insert(std::end(v), std::begin(props), std::end(props));
	}

	v.reserve(this->properties.size() + v.size());

	std::transform(std::begin(this->properties), std::end(this->properties), std::back_inserter(v), [](const auto& x) { return x.get(); });

	return v;
}

bool ReflType::operator==(const ReflType& rhs) const
{
	auto equalsBaseType = true;

	if(this->baseTypeIt != std::end(Reflection::ReflMap))
	{
		equalsBaseType = this->baseTypeIt->second == rhs;
	}

	return this->index == rhs.index || equalsBaseType;
}

void age::utilities::Reflection::Clear()
{
	ReflMap.clear();
}

const ReflType* const age::utilities::Reflection::Get(std::string_view x)
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
