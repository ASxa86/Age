#include <azule/core/ObjectFactory.h>

using namespace azule;

ObjectFactory& ObjectFactory::Instance()
{
	static ObjectFactory singleton;
	return singleton;
}

std::shared_ptr<Object> ObjectFactory::create(std::string_view x) const
{
	const auto foundIt =
		std::find_if(std::begin(this->types), std::end(this->types), [x](auto& type) { return type->name == x || type->alias == x; });

	if(foundIt != std::end(this->types))
	{
		return (*foundIt)->creator->create();
	}

	return nullptr;
}

std::shared_ptr<Object> ObjectFactory::create(const std::type_info& x) const
{
	const auto foundIt =
		std::find_if(std::begin(this->types), std::end(this->types), [&x](auto& type) { return type->typeID == x; });

	if(foundIt != std::end(this->types))
	{
		return (*foundIt)->creator->create();
	}

	return nullptr;
}
