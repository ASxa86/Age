#include <age/entity/FixedSystem.h>
#include <age/entity/VariableSystem.h>
#include <age/entity/SystemManager.h>

using namespace age::entity;

SystemManager::SystemManager()
{
	this->addFixedFunction([this](auto x) {this->updateFixedSystems(x); });
	this->addVariableFunction([this](auto x) {this->updateVariableSystems(x); });
}

SystemManager::~SystemManager()
{
}

void SystemManager::updateFixedSystems(std::chrono::microseconds x)
{
	const auto& entities = this->getParent()->getChild<EntityManager>()->getEntities();
	const auto systems = this->getChildren<FixedSystem>();

	for(const auto& system : systems)
	{
		system->frame(entities, x);
	}
}

void SystemManager::updateVariableSystems(std::chrono::microseconds x)
{
	const auto& entities = this->getParent()->getChild<EntityManager>()->getEntities();
	const auto systems = this->getChildren<VariableSystem>();

	for(const auto& system : systems)
	{
		system->frame(entities, x);
	}
}
