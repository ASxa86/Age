#include <tools/editor/ComponentFactory.h>

#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>
#include <unordered_map>

using namespace age;

struct ComponentFactory::Impl
{
	std::unordered_map<std::string, std::function<void(age::entity::Entity&)>> factoryMapAdd;
	std::unordered_map<std::string, std::function<void(age::entity::Entity&)>> factoryMapRemove;
};

ComponentFactory& ComponentFactory::Instance()
{
	static ComponentFactory singleton;
	return singleton;
}

void ComponentFactory::addComponent(age::entity::Entity& e, const std::string& x)
{
	const auto foundIt = this->pimpl->factoryMapAdd.find(x);

	if(foundIt != std::end(this->pimpl->factoryMapAdd))
	{
		foundIt->second(e);
	}
}

void ComponentFactory::removeComponent(age::entity::Entity& e, const std::string& x)
{
	const auto foundIt = this->pimpl->factoryMapRemove.find(x);

	if(foundIt != std::end(this->pimpl->factoryMapRemove))
	{
		foundIt->second(e);
	}
}

std::vector<std::string> ComponentFactory::getComponentList() const
{
	std::vector<std::string> v;

	for(const auto& [component, f] : this->pimpl->factoryMapAdd)
	{
		v.push_back(component);
	}

	return v;
}

void ComponentFactory::registerAdd(const std::string& x, const std::function<void(age::entity::Entity&)>& f)
{
	this->pimpl->factoryMapAdd[x] = f;
}

void ComponentFactory::registerRemove(const std::string& x, const std::function<void(age::entity::Entity&)>& f)
{
	this->pimpl->factoryMapRemove[x] = f;
}
