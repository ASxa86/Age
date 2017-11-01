#include <age/entity/FixedSystem.h>
#include <age/core/PimplImpl.h>
#include <age/entity/VariableSystem.h>
#include <age/entity/EntityProcessor.h>

using namespace age::entity;

class EntityProcessor::Impl
{
public:
	Impl() : events{}, entities{std::make_unique<entityx::EntityManager>(events)}
	{
	}

	entityx::EventManager events;
	std::unique_ptr<entityx::EntityManager> entities;
};

EntityProcessor::EntityProcessor()
{
}

EntityProcessor::~EntityProcessor()
{
}

entityx::EntityManager* EntityProcessor::getEntities()
{
	return this->pimpl->entities.get();
}

void EntityProcessor::updateFixedSystems(std::chrono::microseconds x)
{
	const auto systems = this->getChildren<FixedSystem>();

	for(const auto& system : systems)
	{
		system->frame(x);
	}
}

void EntityProcessor::updateVariableSystems(std::chrono::microseconds x)
{
	const auto systems = this->getChildren<VariableSystem>();

	for(const auto& system : systems)
	{
		system->frame(x);
	}
}
